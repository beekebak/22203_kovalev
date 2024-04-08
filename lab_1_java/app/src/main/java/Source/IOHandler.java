package Source;

import Exceptions.InputFormatException;

import java.io.*;
import java.util.Scanner;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Writes input lines and prints output.
 * Could be initialized with custom in/out streams.
 * Uses System.in/System.out by default.
 * iter is string iterator that points to character should be read next.
 */

public class IOHandler implements Closeable{
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    private Scanner inputScanner;
    private Writer outputWriter;

    private String inputLine;
    private int iter;

    public IOHandler(){
        this(System.in, System.out);
    }

    public IOHandler(InputStream in, OutputStream out){
        inputScanner = new Scanner(in);
        outputWriter = new PrintWriter(out);
    }

    public void ReadLine(){
        inputLine = inputScanner.next();
        iter = 0;
        log.debug("I/O handler read line {}", inputLine);
    }

    public String GetLine(){
        return inputLine;
    }

    public boolean StringIsOver(){
        return iter >= inputLine.length();
    }

    /**
     * @return next character in input string
     * @throws InputFormatException in case next character should be provided
     * but there isn't any
     */
    public char GetChar() throws InputFormatException {
        if(StringIsOver()){
            log.error("Character was requested after string ended.");
            throw new InputFormatException("necessary character was not provided");
        }
        log.debug("Got character {}", inputLine.charAt(iter));
        return inputLine.charAt(iter++);
    }
    public void Write(char c){
        try {
            outputWriter.write(c);
            outputWriter.flush();
        }
        catch(IOException e) {
            log.error("Exception occurred during writing operation");
        }
    }

    public void Write(String c){
        try {
            outputWriter.write(c);
            outputWriter.flush();
        }
        catch(IOException e) {
            log.error("Exception occurred during writing operation");
        }
    }

    public int GetIter() {
        log.debug("Input string iterator is {}", iter);
        return iter;
    }

    public void SetIter(int iter){
        log.debug("Input string iterator is now {}", iter);
        this.iter = iter;
    }

    public void close(){
        try {
            inputScanner.close();
            outputWriter.close();
        }
        catch(IOException ex){
            log.error("IOHandler close failure");
        }
    }
}
