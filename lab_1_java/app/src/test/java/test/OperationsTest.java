package test;

import Operations.Operation;
import Operations.OperationFactory;
import Source.DataHandler;
import Source.IOHandler;

import Source.Preprocessor;
import org.junit.jupiter.api.*;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;


public class OperationsTest {
    DataHandler dataHandler;
    IOHandler IOhandler;
    Preprocessor preprocessor = new Preprocessor();
    OperationFactory factory = new OperationFactory();
    static final byte[] input =  {1,2,3,4};
    private static final ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();
    private static final ByteArrayInputStream inputStreamCaptor = new ByteArrayInputStream(input);

    @BeforeAll
    public static void SetupOutput(){
        System.setOut(new PrintStream(outputStreamCaptor));
        System.setIn(inputStreamCaptor);
    }
    @BeforeEach
    public void InitializeContext(){
        dataHandler = new DataHandler();
        IOhandler = new IOHandler();
        dataHandler.SetLoopBracketsMap(preprocessor.PreprocessInput("++++>[.....]>---", factory));
    }
    @Test
    public void IncrementTest(){
        Operation op = factory.GetInstance("+");
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals((char) 1, dataHandler.GetData());
    }
    @Test
    public void DecrementTest(){
        dataHandler.SetData('b');
        Operation op = factory.GetInstance("-");
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals('a', dataHandler.GetData());
    }
    @Test
    public void GetterTest(){
        dataHandler.SetData('b');
        Operation op = factory.GetInstance(".");
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals("b", outputStreamCaptor.toString().trim());
    }
    @Test
    public void SetterTest(){
        Operation op = factory.GetInstance(",");
        IOhandler.ReadLine();
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals((char)1, dataHandler.GetData());
    }
    @Test
    public void LeftShiftTest(){
        Operation op = factory.GetInstance("<");
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals(14999, dataHandler.GetDataPointer());
    }
    @Test
    public void RightShiftTest(){
        Operation op = factory.GetInstance(">");
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals(15001, dataHandler.GetDataPointer());
    }
    @Test
    public void CycleEnterTest(){
        Operation op = factory.GetInstance("[");
        IOhandler.SetIter(6);
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals(12, IOhandler.GetIter());
        IOhandler.SetIter(6);
        dataHandler.SetData('1');
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals(6, IOhandler.GetIter());
    }
    @Test
    public void CycleEndTest(){
        Operation op = factory.GetInstance("]");
        op.Operate(dataHandler, IOhandler);
        IOhandler.SetIter(12);
        Assertions.assertEquals(12, IOhandler.GetIter());
        dataHandler.SetData('1');
        op.Operate(dataHandler, IOhandler);
        Assertions.assertEquals(5, IOhandler.GetIter());
    }
}
