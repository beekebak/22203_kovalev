package org.example.Server;

import org.example.Operations.OperationState;
import org.example.Operations.ServerOperation;
import org.example.Utility.ChunkState;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.InetSocketAddress;
import java.net.StandardSocketOptions;
import java.nio.channels.*;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.atomic.AtomicBoolean;

public class ServerFileHandler implements AutoCloseable{
    private final RandomAccessFile file;
    private final Selector selector;
    private final ServerSocketChannel listeningSocket;
    private final ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private final long bufferSize;
    private final AtomicBoolean stopFlag;
    private final Set<ServerOperation> unfinishedOperations;

    public void setStopFlag(boolean flag){
        stopFlag.set(flag);
    }

    public ServerFileHandler(ConcurrentMap<Integer, ChunkState> chunkPresenceMap, long bufferSize, String filePath,
                             boolean stopFlag)
            throws IOException {
        this.file = new RandomAccessFile(filePath, "rw");
        selector = Selector.open();
        listeningSocket = ServerSocketChannel.open();
        this.chunkPresenceMap = chunkPresenceMap;
        this.bufferSize = bufferSize;
        this.stopFlag = new AtomicBoolean(stopFlag);
        unfinishedOperations = new HashSet<>();
    }

    public void startServer(int socketPort) throws IOException {
        listeningSocket.bind(new InetSocketAddress("localhost", socketPort));
        listeningSocket.configureBlocking(false);
        listeningSocket.register(selector, SelectionKey.OP_ACCEPT);
        while(true){
            if(stopFlag.get()) return;
            selector.select(1);
            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> iter = selectedKeys.iterator();
            while (iter.hasNext()) {
                SelectionKey key = iter.next();
                handleKey(key);
                iter.remove();
            }
            var undoneOpsIter = unfinishedOperations.iterator();
            while (undoneOpsIter.hasNext()) {
                ServerOperation operation = undoneOpsIter.next();
                OperationState result = operation.writeToSocket();
                if(result == OperationState.DONE || result == OperationState.CANCELLED) undoneOpsIter.remove();
            }
        }
    }

    private void handleKey(SelectionKey key) throws IOException {
        if (key.isAcceptable()) {
            acceptConnection();
        } else if (key.isReadable()) {
            handleInput(key);
        }
    }

    private void acceptConnection() throws IOException {
        SocketChannel socket = listeningSocket.accept();
        socket.setOption(StandardSocketOptions.SO_SNDBUF, (int)bufferSize);
        socket.configureBlocking(false);
        socket.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);
    }

    private void handleInput(SelectionKey key) throws IOException {
        ServerOperation serverOperation = new ServerOperation(bufferSize, key, file, chunkPresenceMap);
        OperationState state = serverOperation.handleInput();
        if(state == OperationState.CANCELLED){
            key.channel().close();
            key.cancel();
        }
        else if(state == OperationState.SENDING_PROCESS){
            key.cancel();
            unfinishedOperations.add(serverOperation);
        }
    }

    @Override
    public void close() throws Exception {
        if(listeningSocket.isOpen()) listeningSocket.close();
        if(selector.isOpen()) selector.close();
        file.close();
    }
}
