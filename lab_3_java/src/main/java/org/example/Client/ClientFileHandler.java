package org.example.Client;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Utility.ChunkState;
import org.example.Operations.OperationState;

import java.io.Closeable;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.InetSocketAddress;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.atomic.AtomicBoolean;

public class ClientFileHandler implements Closeable {
    private final RandomAccessFile file;
    private final Selector selector;
    private final ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private final BlockingQueue<Integer> chunksToRegister;
    private final BlockingQueue<Integer> chunksToRelease;
    private final long chunkSize;
    private long unloadedChunksCount;
    private List<InetSocketAddress> peers;
    private final Map<SelectionKey, ChunkLoader> keyToChunkLoaderMap;
    private static final Logger logger = LogManager.getLogger();
    private final boolean log;
    private final PeerChecker peerChecker;
    private final AtomicBoolean peersCheckIsNeeded = new AtomicBoolean(true);

    public ClientFileHandler(String filepath, long chunkSize, List<InetSocketAddress> peers, long unloadedChunksCount,
                             ConcurrentMap<Integer, ChunkState> chunkPresenceMap, boolean log)
            throws IOException {
        this.log = log;
        file = new RandomAccessFile(filepath, "rw");
        selector = Selector.open();
        this.chunkPresenceMap = chunkPresenceMap;
        chunksToRegister = new ArrayBlockingQueue<>(20);
        chunksToRelease = new ArrayBlockingQueue<>(20);
        this.chunkSize = chunkSize;
        this.unloadedChunksCount = unloadedChunksCount;
        peerChecker = new PeerChecker(peers);
        keyToChunkLoaderMap = new HashMap<>();
        checkPeers();
    }

    private void checkPeers(){
        peers = peerChecker.checkPeers();
        peersCheckIsNeeded.set(false);
    }

    private void initializeHandover(SelectionKey key) throws IOException {
        if (!((SocketChannel) key.channel()).finishConnect()) return;
        OperationState state = keyToChunkLoaderMap.get(key).initializeHandover(key);
        if (state == OperationState.CANCELLED) {
            log("Cancelled after connection before request chunk " + keyToChunkLoaderMap.get(key).getOffset());
            chunkPresenceMap.replace(keyToChunkLoaderMap.get(key).getOffset(), ChunkState.EMPTY);
            keyToChunkLoaderMap.remove(key);
            key.channel().close();
            key.cancel();
        } else{
            log("requested after connection chunk " + keyToChunkLoaderMap.get(key).getOffset());
            chunkPresenceMap.replace(keyToChunkLoaderMap.get(key).getOffset(), ChunkState.REQUESTED);
        }
    }

    private void handleRejectedRequest(ChunkLoader loader, SelectionKey key) throws IOException {
        log("cancelled after request new connection chunk " + keyToChunkLoaderMap.get(key).getOffset());
        handleCancelledConnection(loader, key);
        OperationState state = loader.registerConnection(keyToChunkLoaderMap);
        if(state == OperationState.INITIALIZED_CONNECTION){
            chunkPresenceMap.replace(loader.getOffset(), ChunkState.REQUESTED);
        }
    }

    private void handleDoneRequest(ChunkLoader loader, SelectionKey key) throws IOException{
        log("done chunk " + keyToChunkLoaderMap.get(key).getOffset());
        if(chunkPresenceMap.get(loader.getOffset()) != ChunkState.GOT) unloadedChunksCount--;
        chunkPresenceMap.replace(loader.getOffset(), ChunkState.GOT);
        keyToChunkLoaderMap.remove(key);
        key.channel().close();
        key.cancel();
    }

    private void handleCancelledConnection(ChunkLoader loader, SelectionKey key) throws IOException{
        log("cancelled while waiting input chunk " + keyToChunkLoaderMap.get(key).getOffset());
        peersCheckIsNeeded.set(true);
        chunkPresenceMap.replace(loader.getOffset(), ChunkState.EMPTY);
        keyToChunkLoaderMap.remove(key);
        key.channel().close();
        key.cancel();
    }

    private void handleActiveKey(Iterator<SelectionKey> keyIterator) throws IOException{
        SelectionKey key = keyIterator.next();
        if (key.isConnectable()) initializeHandover(key);
        else if (key.isReadable()) {
            ChunkLoader loader = keyToChunkLoaderMap.get(key);
            OperationState state = loader.getChunk(key);
            if(state == OperationState.ANSWERED_CHECK_NO) handleRejectedRequest(loader, key);
            else if (state == OperationState.DONE) handleDoneRequest(loader, key);
            else if (state == OperationState.CANCELLED) handleCancelledConnection(loader, key);
        }
        keyIterator.remove();
    }

    private void fillSelector(int currentSize, Set<Integer> activeChunksNumbers){
        while (currentSize < 20 && !chunksToRegister.isEmpty()) {
            currentSize++;
            int offset;
            try {
                offset = chunksToRegister.take();
            } catch (InterruptedException exception) {
                throw new RuntimeException(exception);
            }
            if(chunkPresenceMap.get(offset) != ChunkState.EMPTY || activeChunksNumbers.contains(offset)){
                currentSize--;
                continue;
            }
            ChunkLoader loader = new ChunkLoader(chunkSize, selector, file, peers, offset);
            OperationState state = loader.registerConnection(keyToChunkLoaderMap);
            activeChunksNumbers.add(offset);
            if (state == OperationState.CANCELLED) {
                currentSize--;
                log("tried to start but failed chunk " + offset);
            }
            else log("started chunk " + offset);
        }
    }

    private void fixHangingConnections(Set<Integer> activeChunksNumbers){
        while(!chunksToRelease.isEmpty()){
            int offset;
            try {
                offset = chunksToRelease.take();
            } catch (InterruptedException exception) {
                throw new RuntimeException(exception);
            }
            if(!activeChunksNumbers.contains(offset) && chunkPresenceMap.get(offset) == ChunkState.REQUESTED) {
                chunkPresenceMap.replace(offset, ChunkState.EMPTY);
                log("cleared hanging requested chunk " + offset);
            }
        }
    }

    private void updateSelector(){
        int currentSize = selector.keys().size();
        Set<Integer> activeChunksNumbers = new HashSet<>();
        keyToChunkLoaderMap.entrySet().removeIf(entry -> !entry.getKey().isValid());
        for(var chunk:keyToChunkLoaderMap.values()){
            activeChunksNumbers.add(chunk.getOffset());
        }
        fillSelector(currentSize, activeChunksNumbers);
        fixHangingConnections(activeChunksNumbers);
    }

    public void downloadFile() {
        Thread fileLoaderThread = new Thread(new FileLoader(chunkPresenceMap, chunksToRegister, chunksToRelease));
        fileLoaderThread.start();
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                peersCheckIsNeeded.set(true);
            }
        }, 0, 30*1000);
        while (unloadedChunksCount > 0) {
            try {
                if (peersCheckIsNeeded.get()) checkPeers();
                selector.select(1000);
                Set<SelectionKey> selectionKeys = selector.selectedKeys();
                Iterator<SelectionKey> keyIterator = selectionKeys.iterator();
                while (keyIterator.hasNext()) handleActiveKey(keyIterator);
                updateSelector();
            } catch (IOException ignored) {}
        }
        try {
            fileLoaderThread.join();
        } catch(InterruptedException ignored){}
    }

    private void log(String msg){
        if(!log) return;
        logger.info(msg);
    }

    @Override
    public void close() throws IOException {
        if(selector.isOpen()) selector.close();
        file.close();
    }
}
