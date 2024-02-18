package Source;

import Exceptions.InputFormatException;

import java.io.*;
import java.util.Scanner;

public class IOHandler {
    private Scanner inputScanner;
    private Writer outputWriter;

    private String inputLine;
    int iter;

    IOHandler(){
        this(System.in, System.out);
    }

    IOHandler(InputStream in, OutputStream out){
        inputScanner = new Scanner(in);
        outputWriter = new PrintWriter(out);
    }

    void ReadLine(){
        inputLine = inputScanner.next();
        iter = 0;
    }

    String GetLine(){
        return inputLine;
    }

    public boolean StringIsOver(){
        return iter == inputLine.length();
    }

    public char GetChar() throws InputFormatException {
        if(StringIsOver()) throw new InputFormatException("necessary was not provided");
        return inputLine.charAt(iter++);
    }
    public void Write(char c){
        try {
            outputWriter.write(c);
            outputWriter.flush();
        }
        catch(IOException e) {}
    }

    public int GetIter() {
        return iter;
    }

    public void SetIter(int iter){
        this.iter = iter;
    }
}
