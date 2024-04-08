package test;

import Operations.OperationFactory;
import Source.ExecutionContext;
import Source.Preprocessor;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class ExecutionContextTest {
    private ExecutionContext context;

    @BeforeEach
    public void InitializeExecutionContext(){
        context = new ExecutionContext();
    }
    @Test
    public void SettersDataTest(){
        Assertions.assertThrows(ArrayStoreException.class, () -> context.SetData((char)-1));
        Assertions.assertThrows(ArrayStoreException.class, () -> context.SetData((char)257));
        Assertions.assertThrows(IndexOutOfBoundsException.class, () -> context.SetDataPointer(-1));
        Assertions.assertThrows(IndexOutOfBoundsException.class, () -> context.SetDataPointer(35337));
    }
    @Test
    public void CheckBracketsMethods(){
        Preprocessor preprocessor = new Preprocessor();
        OperationFactory factory = new OperationFactory();
        context.SetLoopBracketsMap(preprocessor.PreprocessInput("++++>[..[..].]>---", factory));
        Assertions.assertEquals(13, context.GetClosingBracketIndex(5));
        Assertions.assertEquals(11, context.GetClosingBracketIndex(8));
        Assertions.assertEquals(8, context.GetOpeningBracketIndex(11));
        Assertions.assertEquals(5, context.GetOpeningBracketIndex(13));
    }
}
