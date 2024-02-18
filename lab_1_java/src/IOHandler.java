package src;

import java.io.*;
import java.util.Scanner;

public class IOHandler {
    private Scanner inputScanner;
    private Writer outputWriter;

    IOHandler(){
        this(System.in, System.out);
    }

    IOHandler(InputStream in, OutputStream out){
        inputScanner = new Scanner(in);
        outputWriter = new PrintWriter(out);
    }

    public String ReadLine(){
        return inputScanner.next();
    }

    void Write(String line) throws IOException{
        outputWriter.write(line);
    }

    void Write(char c) throws IOException{
        outputWriter.write(c);
    }
}
