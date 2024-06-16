package org.example.Client;

import lombok.AllArgsConstructor;
import org.example.Utility.ChunkState;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentMap;

@AllArgsConstructor
public class FileLoader implements Runnable {
    private ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private BlockingQueue<Integer> chunksToRegister;

    @Override
    public void run() {
        while(true) {
            boolean fileIsLoaded = true;
            for (var chunk : chunkPresenceMap.entrySet()) {
                if (chunk.getValue() == ChunkState.REQUESTED) {
                    fileIsLoaded = false;
                }
                else if (chunk.getValue() == ChunkState.EMPTY) {
                    try {
                        chunksToRegister.put(chunk.getKey());
                    } catch (InterruptedException ignored) {}
                    fileIsLoaded = false;
                }
            }
            if(fileIsLoaded) break;
        }
    }
}
