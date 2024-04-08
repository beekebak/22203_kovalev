package test;

import Source.BrainFuck;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

public class BrainFuckTest {
    private BrainFuck bf;
    private ByteArrayInputStream inputStreamCaptor;

    @Test
    public void LeavesCorrectly() {
        byte[] quit = {'q', 'u', 'i', 't'};
        inputStreamCaptor = new ByteArrayInputStream(quit);
        bf = new BrainFuck(inputStreamCaptor, System.out);
        bf.Work();
    }
    @Test
    public void LeavesCorrectlyOnException(){
        byte[] qui = {'q', 'u', 'i'};
        inputStreamCaptor = new ByteArrayInputStream(qui);
        bf = new BrainFuck(inputStreamCaptor, System.out);
        bf.Work();
    }
}
