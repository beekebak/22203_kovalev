package org.example.Server;

import org.example.Utility.ChunkState;
import org.example.Utility.FileParser;

import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.ConcurrentMap;

public class Server {
    private final int port;
    private final String filePath;
    private final ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private final long chunkSize;

    public Server(int port, String filePath, FileParser parser){
        this.filePath = filePath;
        this.port = port;
        this.chunkSize = parser.getChunkSize();
        this.chunkPresenceMap = parser.getChunkStateMap();
    }

    public void startServer() {
        try(ServerFileHandler fileHandler = new ServerFileHandler(chunkPresenceMap, chunkSize, filePath, false)){
            Thread thread = new Thread(() -> {
                try {
                    fileHandler.startServer(port);
                } catch (IOException ignored) {}
            });
            thread.start();
            String input = "";
            Scanner inputScanner = new Scanner(System.in);
            while(!input.equals("quit")){
                input = inputScanner.next();
            }
            fileHandler.setStopFlag(true);
            thread.join();
        } catch (Exception ignored) {
            try {
                wait(10000);
            } catch(Exception ignored1) {}
            startServer();
        }
    }
}
