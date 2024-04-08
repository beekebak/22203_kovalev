package test;

import Source.BrainFuck;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class BrainFuckTest {
    BrainFuck bf;
    private ByteArrayInputStream inputStreamCaptor;
    @BeforeEach
    public void Setup(){
        bf = new BrainFuck();
    }

    @Test
    public void LeavesCorrectly(){
        byte[] quit = {'q', 'u', 'i', 't'};
        inputStreamCaptor = new ByteArrayInputStream(quit);
        System.setIn(inputStreamCaptor);
        bf.Work();
        byte[] qui = {'q', 'u', 'i'};
        inputStreamCaptor = new ByteArrayInputStream(qui);
        System.setIn(inputStreamCaptor);
        bf.Work();
    }
}
