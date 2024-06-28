package org.example.Operations;

import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.SocketChannel;

public abstract class Operation {
    protected ByteBuffer buffer;
    protected SelectionKey key;
    protected RandomAccessFile file;
    protected long chunkSize;
    protected OperationState state;
    protected SocketChannel socket;

    public Operation(long chunkSize, SelectionKey key, RandomAccessFile file, ByteBuffer buffer) {
        this.chunkSize = chunkSize;
        this.buffer = buffer;
        this.file = file;
        this.key = key;
        socket = (SocketChannel) key.channel();
    }

    public Operation(long chunkSize, SelectionKey key, RandomAccessFile file){
        this(chunkSize, key, file, ByteBuffer.allocate((int)chunkSize));
    }

    protected void handleError(String msg){
        state = OperationState.CANCELLED;
        System.out.println(msg);
    }
}
