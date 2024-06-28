package org.example;

import org.example.Client.Client;
import org.example.Server.Server;
import org.example.Utility.FileParser;
import java.io.IOException;


public class Main {
    public static void main(String[] args) {
         try {
            FileParser parser = new FileParser(args[2], args[3], args[1]);
            Client client = new Client(args[1], parser);
            Server server = new Server(Integer.parseInt(args[0]), args[1], parser);
            Thread clientThread = new Thread(client::startClient);
            Thread serverThread = new Thread(server::startServer);
            clientThread.start();
            serverThread.start();
            try {
                clientThread.join();
                System.out.println("done");
                serverThread.join();
            } catch (InterruptedException ignored) {}
        } catch (IOException ignored){
            System.out.println("couldn't start application");
        }
         System.out.println("work end");
    }
}