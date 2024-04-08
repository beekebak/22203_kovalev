package test;

import Source.BrainFuck;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

public class ProgramTest {
    @Test
    public void PrintHelloWorld(){
        String helloWorld = ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.>>>++++++++[<++++>-]" +
                "<.>>>++++++++++[<+++++++++>-]<---.<<<<.+++.------.--------.>>+.>++++++++++.\n"+
                "quit";

        ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();
        ByteArrayInputStream inputStreamCaptor = new ByteArrayInputStream(helloWorld.getBytes());
        BrainFuck brainFuck = new BrainFuck(inputStreamCaptor, outputStreamCaptor);
        brainFuck.Work();
        Assertions.assertEquals("Hello World!\n", outputStreamCaptor.toString());
    }
}
