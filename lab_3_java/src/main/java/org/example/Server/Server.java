package org.example.Server;

import org.example.Utility.ChunkState;
import org.example.Utility.FileParser;

import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.atomic.AtomicBoolean;

public class Server {
    private final int port;
    private FileParser parser;
    private final String filePath;
    private ConcurrentMap<Integer, ChunkState> chunkPresenceMap;
    private int chunkSize;

    public Server(int port, String filePath, String cfgPath){
        this.filePath = filePath;
        this.port = port;
        try {
            parser = new FileParser(cfgPath);
            chunkPresenceMap = parser.getMap();
            chunkSize = parser.getChunkSize();
        } catch(Exception ignored) {}
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
