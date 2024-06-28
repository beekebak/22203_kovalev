package org.example.Client;

import org.example.Utility.ChunkState;
import org.example.Utility.FileParser;

import java.net.InetSocketAddress;
import java.util.List;
import java.util.concurrent.ConcurrentMap;

public class Client {
    private final String filePath;
    private final ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private final long chunkSize;
    private long unloadedChunksCount;
    private final List<InetSocketAddress> peers;
    private final FileParser parser;

    public Client(String filePath, FileParser parser){
        this.filePath = filePath;
        this.chunkSize = parser.getChunkSize();
        this.chunkPresenceMap = parser.getChunkStateMap();
        this.peers = parser.getPeers();
        this.unloadedChunksCount = parser.getNeededChunksCount();
        this.parser = parser;
    }

    public void startClient(){
        try(ClientFileHandler fileHandler = new ClientFileHandler(filePath, chunkSize, peers, unloadedChunksCount,
                chunkPresenceMap)){
            fileHandler.downloadFile();
        } catch (Exception ignored) {
            try {
                parser.rebuildMap();
                unloadedChunksCount = parser.getNeededChunksCount();
                wait(10000);
            } catch(Exception ignored1) {}
            startClient();
        }
    }
}
