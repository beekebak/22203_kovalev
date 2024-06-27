package org.example.Utility;

import be.christophedetroyer.bencoding.Utils;
import be.christophedetroyer.torrent.Torrent;
import be.christophedetroyer.torrent.TorrentParser;
import lombok.Getter;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

@Getter
public class FileParser {
    long chunkSize;
    long totalSize;
    long neededChunksCount = 0;
    ConcurrentMap<Integer, ChunkState> chunkStateMap;
    List<InetSocketAddress> peers;
    Torrent torrent;
    String actualFilePath;

    public FileParser(String configPath, String torrentFilePath, String actualFilePath) throws IOException {
        this.actualFilePath = actualFilePath;
        parseConfig(configPath);
        parseTorrent(torrentFilePath);
    }

    private void buildMap() throws IOException{
        try(FileChannel fileChannel = FileChannel.open(Path.of(actualFilePath),StandardOpenOption.READ)) {
            for (int i = 0; i < torrent.getPieces().size(); i++) {
                long from = i * chunkSize;
                long toSize = Math.min(chunkSize, fileChannel.size() - from);
                if(toSize > 0){
                    ByteBuffer buffer = fileChannel.map(FileChannel.MapMode.READ_ONLY, from, toSize);
                    buffer.rewind();
                    byte[] arr = new byte[buffer.remaining()];
                    buffer.get(arr);
                    String hash = Utils.SHAsum(arr);
                    if(chunkStateMap.containsKey(i)){
                        if(hash.equalsIgnoreCase(torrent.getPieces().get(i)) && chunkStateMap.get(i) != ChunkState.GOT){
                            chunkStateMap.replace(i, ChunkState.GOT);
                            neededChunksCount--;
                        }
                        else if(chunkStateMap.get(i) != ChunkState.EMPTY){
                            neededChunksCount++;
                            chunkStateMap.replace(i, ChunkState.EMPTY);
                        }
                    }
                    else{
                        if(hash.equalsIgnoreCase(torrent.getPieces().get(i))) chunkStateMap.put(i, ChunkState.GOT);
                        else {
                            chunkStateMap.put(i, ChunkState.EMPTY);
                            neededChunksCount++;
                        }
                    }
                }
            }
        }
    }

    private void handleEmptyActualFile(File actualFile) throws IOException {
        actualFile.createNewFile();
        try(RandomAccessFile truncFile = new RandomAccessFile(actualFile, "rw")){
            truncFile.seek(totalSize);
        }
        for(int i = 0; i < torrent.getPieces().size(); i++){
            chunkStateMap.put(i, ChunkState.EMPTY);
        }
        neededChunksCount = torrent.getPieces().size();
    }

    private void parseTorrent(String torrentFilePath) throws IOException {
        torrent = TorrentParser.parseTorrent(torrentFilePath);
        chunkSize = torrent.getPieceLength();
        if(torrent.getTotalSize() != null) totalSize = torrent.getTotalSize();
        else totalSize = chunkSize * torrent.getPieces().size();
        chunkStateMap = new ConcurrentHashMap<>();
        File actualFile = new File(actualFilePath);
        if(actualFile.exists()) buildMap();
        else handleEmptyActualFile(actualFile);
    }

    private void parseConfig(String configPath) throws IOException {
        try(BufferedReader reader = new BufferedReader(new FileReader(configPath))) {
            peers = new ArrayList<>();
            String peer;
            while (true) {
                peer = reader.readLine();
                if (peer == null) break;
                peers.add(new InetSocketAddress(Integer.parseInt(peer)));
            }
        }
    }

    public void rebuildMap() throws IOException{
        buildMap();
    }
}
