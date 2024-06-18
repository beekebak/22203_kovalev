package org.example.Client;

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

public class ClientFileHandler implements Closeable {
    private final RandomAccessFile file;
    private final Selector selector;
    private final ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private final BlockingQueue<Integer> chunksToRegister;
    private final int chunkSize;
    private int unloadedChunksCount;
    private final List<InetSocketAddress> peers;
    private final Map<SelectionKey, ChunkLoader> keyToChunkLoaderMap;
    public ClientFileHandler(String filepath, int chunkSize, List<InetSocketAddress> peers,
                             ConcurrentMap<Integer, ChunkState> chunkPresenceMap)
            throws IOException {
        file = new RandomAccessFile(filepath, "rw");
        selector = Selector.open();
        this.chunkPresenceMap = chunkPresenceMap;
        chunksToRegister = new ArrayBlockingQueue<>(20);
        this.chunkSize = chunkSize;
        unloadedChunksCount = chunkPresenceMap.size();
        this.peers = peers;
        keyToChunkLoaderMap = new HashMap<>();
    }

    public void downloadFile() throws IOException {
        Thread fileLoaderThread = new Thread(new FileLoader(chunkPresenceMap, chunksToRegister));
        fileLoaderThread.start();
        while (unloadedChunksCount > 0) {
            selector.select(1000);
            Set<SelectionKey> selectionKeys = selector.selectedKeys();
            Iterator<SelectionKey> keyIterator = selectionKeys.iterator();
            while (keyIterator.hasNext()) {
                SelectionKey key = keyIterator.next();
                if (key.isConnectable()) {
                    if (!((SocketChannel) key.channel()).finishConnect()) continue;
                    OperationState state = keyToChunkLoaderMap.get(key).initializeHandover(key);
                    if (state == OperationState.CANCELLED) {
                        chunkPresenceMap.replace(keyToChunkLoaderMap.get(key).getOffset(), ChunkState.EMPTY);
                        keyToChunkLoaderMap.remove(key);
                        key.channel().close();
                        key.cancel();
                    } else{
                        chunkPresenceMap.replace(keyToChunkLoaderMap.get(key).getOffset(), ChunkState.REQUESTED);
                    }
                }
                else if (key.isReadable()) {
                    ChunkLoader loader = keyToChunkLoaderMap.get(key);
                    OperationState state = loader.getChunk(key, keyToChunkLoaderMap);
                    if(state == OperationState.ANSWERED_CHECK_NO){
                        key.channel().close();
                        keyToChunkLoaderMap.remove(key);
                        key.cancel();
                        chunkPresenceMap.replace(loader.getOffset(), ChunkState.EMPTY);
                        state = loader.registerConnection(keyToChunkLoaderMap);
                        if(state == OperationState.INITIALIZED_CONNECTION){
                            chunkPresenceMap.replace(loader.getOffset(), ChunkState.REQUESTED);
                        }
                    }
                    else if (state == OperationState.DONE) {
                        unloadedChunksCount--;
                        chunkPresenceMap.replace(loader.getOffset(), ChunkState.GOT);
                        keyToChunkLoaderMap.remove(key);
                        key.channel().close();
                        key.cancel();
                    } else if (state == OperationState.CANCELLED) {
                        chunkPresenceMap.replace(loader.getOffset(), ChunkState.EMPTY);
                        keyToChunkLoaderMap.remove(key);
                        key.channel().close();
                        key.cancel();
                    }
                }
                keyIterator.remove();
            }
            int currentSize = selector.keys().size();
            while (currentSize < 50 && !chunksToRegister.isEmpty()) {
                currentSize++;
                int offset;
                try {
                    offset = chunksToRegister.take();
                } catch (InterruptedException exception) {
                    throw new RuntimeException(exception);
                }
                if(chunkPresenceMap.get(offset) != ChunkState.EMPTY){
                    currentSize--;
                    continue;
                }
                ChunkLoader loader = new ChunkLoader(chunkSize, selector, file, peers, offset);
                OperationState state = loader.registerConnection(keyToChunkLoaderMap);
                if (state == OperationState.CANCELLED) currentSize--;
            }
        }
        try {
            fileLoaderThread.join();
        } catch(InterruptedException ignored){}
    }

    @Override
    public void close() throws IOException {
        if(selector.isOpen()) selector.close();
        file.close();
    }
}