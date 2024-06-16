package org.example.Utility;

import org.example.Utility.ChunkState;

import java.io.*;
import java.net.InetSocketAddress;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

public class FileParser {
    int size;
    String path;
    BufferedReader reader;
    public FileParser(String path) throws FileNotFoundException {
        this.path = path;
        reader = new BufferedReader(new FileReader(path));
    }
    public ConcurrentMap<Integer, ChunkState> getMap() throws IOException {
        size = Integer.parseInt(reader.readLine());
        String mode = reader.readLine();
        int number = mode.charAt(6) - '0';
        ConcurrentMap<Integer, ChunkState> map = new ConcurrentHashMap<>();
        for(int i = 0; i < size; i++){
            map.put(i, ChunkState.EMPTY);
        }
        if(number != 0) {
            for (int i = (number-1)*size/4; i < number*size/4; i++) {
                map.replace(i, ChunkState.GOT);
            }
        }
        return map;
    }

    public int getChunkSize(){
        return 1024;
    }

    public List<InetSocketAddress> getPeers() throws IOException {
        List<InetSocketAddress> answer = new ArrayList<>();
        String peer = "";
        while(true){
            peer = reader.readLine();
            if(peer == null) break;
            answer.add(new InetSocketAddress(Integer.parseInt(peer)));
        }
        return answer;
    }

}
