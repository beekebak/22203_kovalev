package test;

import Operations.Operation;
import Operations.OperationFactory;
import Source.ExecutionContext;
import Source.IOHandler;

import Source.Preprocessor;
import org.junit.jupiter.api.*;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;


public class OperationsTest {
    ExecutionContext context;
    IOHandler IOhandler;
    Preprocessor preprocessor = new Preprocessor();
    OperationFactory factory = new OperationFactory();
    static final byte[] input =  {1,2,3,4};
    private static final ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();
    private static final ByteArrayInputStream inputStreamCaptor = new ByteArrayInputStream(input);

    @BeforeEach
    public void InitializeContext(){
        context = new ExecutionContext();
        IOhandler = new IOHandler(inputStreamCaptor, outputStreamCaptor);
        context.SetLoopBracketsMap(preprocessor.PreprocessInput("++++>[.....]>---", factory));
    }
    @Test
    public void IncrementTest(){
        Operation op = factory.GetInstance("+");
        op.Operate(context, IOhandler);
        Assertions.assertEquals((char) 1, context.GetData());
    }
    @Test
    public void DecrementTest(){
        context.SetData('b');
        Operation op = factory.GetInstance("-");
        op.Operate(context, IOhandler);
        Assertions.assertEquals('a', context.GetData());
    }
    @Test
    public void GetterTest(){
        context.SetData('b');
        Operation op = factory.GetInstance(".");
        op.Operate(context, IOhandler);
        Assertions.assertEquals("b", outputStreamCaptor.toString().trim());
    }
    @Test
    public void SetterTest(){
        Operation op = factory.GetInstance(",");
        IOhandler.ReadLine();
        op.Operate(context, IOhandler);
        Assertions.assertEquals((char)1, context.GetData());
    }
    @Test
    public void LeftShiftTest(){
        Operation op = factory.GetInstance("<");
        op.Operate(context, IOhandler);
        Assertions.assertEquals(14999, context.GetDataPointer());
    }
    @Test
    public void RightShiftTest(){
        Operation op = factory.GetInstance(">");
        op.Operate(context, IOhandler);
        Assertions.assertEquals(15001, context.GetDataPointer());
    }
    @Test
    public void CycleEnterTest(){
        Operation op = factory.GetInstance("[");
        IOhandler.SetIter(6);
        op.Operate(context, IOhandler);
        Assertions.assertEquals(12, IOhandler.GetIter());
        IOhandler.SetIter(6);
        context.SetData('1');
        op.Operate(context, IOhandler);
        Assertions.assertEquals(6, IOhandler.GetIter());
    }
    @Test
    public void CycleEndTest(){
        Operation op = factory.GetInstance("]");
        op.Operate(context, IOhandler);
        IOhandler.SetIter(12);
        Assertions.assertEquals(12, IOhandler.GetIter());
        context.SetData('1');
        op.Operate(context, IOhandler);
        Assertions.assertEquals(5, IOhandler.GetIter());
    }
}
