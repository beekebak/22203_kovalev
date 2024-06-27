package org.example.Operations;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.Utility.ChunkState;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ConcurrentMap;

public class ServerOperation extends Operation {
    private final ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private static final Logger logger = LogManager.getLogger();
    public ServerOperation(long bufferSize, SelectionKey key, RandomAccessFile file,
                           ConcurrentMap<Integer, ChunkState> chunkPresenceMap) {
        super(bufferSize, key, file);
        this.chunkPresenceMap = chunkPresenceMap;
    }

    public OperationState handleInput(){
        try {
            SocketChannel channel = (SocketChannel) key.channel();
            buffer.clear();
            int readSize = channel.read(buffer);
            if (readSize == -1) {
                return state = OperationState.CANCELLED;
            }
            buffer.flip();
            String input = StandardCharsets.UTF_8.decode(buffer).toString();
            if (input.startsWith("CHECK")) {
                channel.write(ByteBuffer.wrap(checkChunkPresence(input).getBytes()));
            } else if (input.startsWith("GET")) {
                ByteBuffer output = getChunk(input);
                if (output == null) return OperationState.CANCELLED;
                else {
                    while(output.hasRemaining()) {
                        int bytesWritten = channel.write(output);
                        if(bytesWritten == -1) return OperationState.CANCELLED;
                        int requestedChunkNumber;
                        try {
                            requestedChunkNumber = Integer.parseInt(input.substring(4));
                        } catch(NumberFormatException exception){
                            return null;
                        }
                        logger.info("sent to socket chunk " + requestedChunkNumber + " total " + bytesWritten);
                    }
                }
            } else {
                return state = OperationState.CANCELLED;
            }
            return state = OperationState.DONE;
        } catch (IOException exception){
            handleError("no input");
            return state = OperationState.CANCELLED;
        }
    }

    private String checkChunkPresence(String request){
        int requestedChunk;
        try {
            requestedChunk = Integer.parseInt(request.substring(6));
        } catch(NumberFormatException exception){
            return "BAD REQUEST";
        }
        if(chunkPresenceMap.get(requestedChunk) == ChunkState.GOT) return "YES";
        return "NO";
    }

    private ByteBuffer getChunk(String request){
        int requestedChunkNumber;
        try {
            requestedChunkNumber = Integer.parseInt(request.substring(4));
        } catch(NumberFormatException exception){
            return null;
        }
        if(chunkPresenceMap.get(requestedChunkNumber) != ChunkState.GOT) return null;
        ByteBuffer requestedChunk = ByteBuffer.allocate((int)chunkSize);
        try {
            file.seek(requestedChunkNumber * chunkSize);
            file.read(requestedChunk.array());
        } catch(IOException exception){
            return null;
        }
        return requestedChunk;
    }
}
