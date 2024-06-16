package org.example.Operations;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;

public class ClientOperation extends Operation {
    private final int offset;

    public ClientOperation(long chunkSize, SelectionKey key, RandomAccessFile file, int offset, OperationState state){
        super(chunkSize, key, file);
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
        String input = StandardCharsets.UTF_8.decode(buffer).toString();
        if(input.equals("BAD REQUEST")) {
            state = OperationState.CANCELLED;
            return;
        }
        file.seek(offset * chunkSize);
        file.write(buffer.array());
        state = OperationState.DONE;
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
            buffer.clear();
            int readSize = inputChannel.read(buffer);
            if (readSize == -1) {
                handleError("no answer");
            }
            buffer.flip();
            if (state == OperationState.REQUESTED_CHECK) {
                handleCheckAnswer();
            } else if (state == OperationState.ANSWERED_CHECK_YES) {
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
