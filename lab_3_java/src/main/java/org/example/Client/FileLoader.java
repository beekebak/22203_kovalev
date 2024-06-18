package org.example.Client;

import lombok.AllArgsConstructor;
import org.example.Utility.ChunkState;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentMap;

@AllArgsConstructor
public class FileLoader implements Runnable {
    private ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private BlockingQueue<Integer> chunksToRegister;
    private BlockingQueue<Integer> chunksToRelease;

    @Override
    public void run() {
        while(true) {
            boolean fileIsLoaded = true;
            for (var chunk : chunkPresenceMap.entrySet()) {
                if (chunk.getValue() == ChunkState.REQUESTED) {
                    chunksToRelease.offer(chunk.getKey());
                    fileIsLoaded = false;
                }
                else if (chunk.getValue() == ChunkState.EMPTY) {
                    chunksToRegister.offer(chunk.getKey());
                    fileIsLoaded = false;
                }
            }
            if(fileIsLoaded) break;
        }
    }
}
