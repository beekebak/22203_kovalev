package org.example.Client;

import org.example.Utility.ChunkState;
import org.example.Utility.FileParser;

import java.net.InetSocketAddress;
import java.util.List;
import java.util.concurrent.ConcurrentMap;

public class Client {
    private FileParser parser;
    private final String filePath;
    private ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private int chunkSize;
    private List<InetSocketAddress> peers;

    public Client(String filePath, String cfgPath){
        this.filePath = filePath;
        try {
            parser = new FileParser(cfgPath);
            chunkPresenceMap = parser.getMap();
            chunkSize = parser.getChunkSize();
            peers = parser.getPeers();
        } catch(Exception ignored) {}
    }

    public void startClient(){
        boolean log = false;
        if(filePath.equals("/home/beekebak/lab3_test/lab3_client0/book.pdf")) log = true;
        try(ClientFileHandler fileHandler = new ClientFileHandler(filePath, chunkSize, peers, chunkPresenceMap, log)){
            fileHandler.downloadFile();
        } catch (Exception ignored) {
            try {
                wait(10000);
            } catch(Exception ignored1) {}
            startClient();
        }
    }
}
