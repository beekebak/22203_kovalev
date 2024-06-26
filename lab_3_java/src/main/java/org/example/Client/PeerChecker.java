package org.example.Client;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.List;

public class PeerChecker {
    private final List<InetSocketAddress> allAvailablePeers;
    public PeerChecker(List<InetSocketAddress> allAvailablePeers){
        this.allAvailablePeers = allAvailablePeers;
    }

    public List<InetSocketAddress> checkPeers(){
        List<InetSocketAddress> actualSocketAddresses = new ArrayList<>();
        for(var address : allAvailablePeers){
            try(SocketChannel checkChannel = SocketChannel.open(address)){
                actualSocketAddresses.add(address);
            } catch(IOException ignored){}
        }
        return actualSocketAddresses;
    }
}
