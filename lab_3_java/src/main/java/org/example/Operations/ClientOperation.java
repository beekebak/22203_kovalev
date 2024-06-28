package org.example.Operations;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;

public class ClientOperation extends Operation {
    private final int offset;

    public ClientOperation(long chunkSize, SelectionKey key, RandomAccessFile file, int offset, ByteBuffer buffer,
                           OperationState state){
        super(chunkSize, key, file, buffer);
        this.state = state;
        this.offset = offset;
    }

    private void checkChunkAvailability() throws IOException {
        String request = "CHECK "+offset;
        socket.write(ByteBuffer.wrap(request.getBytes()));
    }

    private void requestChunk() throws IOException {
        String request = "GET "+offset;
        socket.write(ByteBuffer.wrap(request.getBytes()));
    }

    private void handleCheckAnswer() throws IOException{
        String input = StandardCharsets.UTF_8.decode(buffer).toString();
        switch (input) {
            case "YES" -> {
                state = OperationState.ANSWERED_CHECK_YES;
                requestChunk();
            }
            case "NO" -> state = OperationState.ANSWERED_CHECK_NO;
            case "BAD REQUEST" -> handleError("Check request failed due to request format");
            default -> handleError("Unexpected check answer");
        }
    }

    private void handleGetAnswer() throws IOException{
        if(chunkSize != buffer.limit()){
            state = OperationState.SENDING_PROCESS;
        }
        else {
            file.seek(offset * chunkSize);
            file.write(buffer.array());
            state = OperationState.DONE;
        }
    }

    public OperationState initializeChunkHandover() {
        try {
            checkChunkAvailability();
            state = OperationState.REQUESTED_CHECK;
        } catch (IOException exception){
            handleError(exception.toString());
        }
        return state;
    }

    public OperationState handleInput(){
        try {
            SocketChannel inputChannel = (SocketChannel) key.channel();
            if(state == OperationState.SENDING_PROCESS) buffer.compact();
            else buffer.clear();
            while(true) {
                int readSize = inputChannel.read(buffer);
                if (readSize == -1) {
                    handleError("no answer");
                    break;
                }
                if(readSize == 0) break;
            }
            buffer.flip();
            if (state == OperationState.REQUESTED_CHECK) {
                handleCheckAnswer();
            } else if (state == OperationState.ANSWERED_CHECK_YES || state == OperationState.SENDING_PROCESS) {
                handleGetAnswer();
            } else {
                handleError("unexpected answer");
            }
            return state;
        } catch (IOException exception){
            handleError(exception.toString());
            return state;
        }
    }
}
