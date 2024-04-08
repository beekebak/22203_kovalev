package test;

import Exceptions.InputFormatException;
import Source.IOHandler;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class IOHandlerTest {
    IOHandler handler;
    static final byte[] input =  {1,2,3,4};
    private ByteArrayOutputStream outputStreamCaptor;
    private ByteArrayInputStream inputStreamCaptor;

    @BeforeEach
    public void Setup(){
        ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();
        ByteArrayInputStream inputStreamCaptor = new ByteArrayInputStream(input);
        handler = new IOHandler(inputStreamCaptor, outputStreamCaptor);
        handler.ReadLine();
    }
    @Test
    public void CheckingLengthTest(){
        handler.SetIter(0);
        Assertions.assertFalse(handler.StringIsOver());
        handler.SetIter(4);
        Assertions.assertTrue(handler.StringIsOver());
        handler.SetIter(100);
        Assertions.assertTrue(handler.StringIsOver());
    }
    @Test
    public void GettingCharTest(){
        handler.SetIter(0);
        Assertions.assertEquals((char) 1, handler.GetChar());
        handler.SetIter(4);
        Assertions.assertThrows(InputFormatException.class, () -> handler.GetChar());
        handler.SetIter(100);
        Assertions.assertThrows(InputFormatException.class, () -> handler.GetChar());
    }
}
