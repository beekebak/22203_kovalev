package test;

import Source.BrainFuck;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class ProgrammTest {
    @Test
    public void PrintHelloWorld(){
        String helloWorld = ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.>>>++++++++[<++++>-]" +
                "<.>>>++++++++++[<+++++++++>-]<---.<<<<.+++.------.--------.>>+.>++++++++++.\n"+
                "quit";

        ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();
        ByteArrayInputStream inputStreamCaptor = new ByteArrayInputStream(helloWorld.getBytes());
        System.setOut(new PrintStream(outputStreamCaptor));
        System.setIn(inputStreamCaptor);
        BrainFuck brainFuck = new BrainFuck();
        brainFuck.Work();
        Assertions.assertEquals("Hello World!\n", outputStreamCaptor.toString());
    }
}
