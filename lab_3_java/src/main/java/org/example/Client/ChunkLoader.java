package org.example.Client;

import lombok.Getter;
import org.example.Operations.ClientOperation;
import org.example.Operations.OperationState;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.InetSocketAddress;
import java.net.StandardSocketOptions;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.*;


public class ChunkLoader {
    private final long chunkSize;
    private final Selector selector;
    private final RandomAccessFile file;
    private final List<InetSocketAddress> peers;
    @Getter
    private final int offset;
    private int startingPeerNumber;
    private int triedPeerNumber;
    private OperationState lastState;
    private ByteBuffer buffer;

    public ChunkLoader(long chunkSize, Selector selector, RandomAccessFile file, List<InetSocketAddress> peers,
                       int offset){
        this.chunkSize = chunkSize;
        this.selector = selector;
        this.file = file;
        this.peers = peers;
        this.offset = offset;
        buffer = ByteBuffer.allocate((int) chunkSize);
        Random random = new Random();
        startingPeerNumber = peers.size() > 1 ? random.nextInt(0, peers.size()-1) : 0;
    }

     public OperationState registerConnection(Map<SelectionKey, ChunkLoader> keyToChunkLoaderMap){
        SocketChannel socket = null;
        try {
            socket = SocketChannel.open();
            socket.setOption(StandardSocketOptions.SO_RCVBUF, (int)chunkSize);
            socket.configureBlocking(false);
            socket.connect(peers.get(startingPeerNumber));
            SelectionKey key = socket.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE |
                    SelectionKey.OP_CONNECT);
            keyToChunkLoaderMap.put(key, this);
        } catch(IOException exception){
            try {
                if (socket != null) socket.close();
            } catch(IOException ignored){
                return lastState = OperationState.CANCELLED;
            }
        }
        lastState =  OperationState.INITIALIZED_CONNECTION;
        return lastState;
    }

    public OperationState initializeHandover(SelectionKey key){
        try{
            ClientOperation operation = new ClientOperation(chunkSize, key, file, offset, buffer, lastState);
            lastState = operation.initializeChunkHandover();
        } catch (Exception e) {
            lastState = OperationState.CANCELLED;
        }
        return lastState;
    }

    public OperationState getChunk(SelectionKey key){
        try{
            ClientOperation operation = new ClientOperation(chunkSize, key, file, offset, buffer, lastState);
            lastState = operation.handleInput();
            if (lastState == OperationState.ANSWERED_CHECK_NO) {
                startingPeerNumber = (startingPeerNumber + 1) % peers.size();
                triedPeerNumber++;
                if(triedPeerNumber == peers.size()) return OperationState.CANCELLED;
            }
        } catch (Exception e) {
            lastState = OperationState.CANCELLED;
        }
        return lastState;
    }
}
