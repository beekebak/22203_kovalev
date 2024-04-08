package test;

import Operations.OperationFactory;
import Source.DataHandler;
import Source.Preprocessor;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class DataHandlerTest {
    DataHandler dataHandler;

    @BeforeEach
    public void InitializeDataHandler(){
        dataHandler = new DataHandler();
    }
    @Test
    public void SettersDataTest(){
        Assertions.assertThrows(ArrayStoreException.class, () -> dataHandler.SetData((char)-1));
        Assertions.assertThrows(ArrayStoreException.class, () -> dataHandler.SetData((char)257));
        Assertions.assertThrows(IndexOutOfBoundsException.class, () -> dataHandler.SetDataPointer(-1));
        Assertions.assertThrows(IndexOutOfBoundsException.class, () -> dataHandler.SetDataPointer(35337));
    }
    @Test
    public void CheckBracketsMethods(){
        Preprocessor preprocessor = new Preprocessor();
        OperationFactory factory = new OperationFactory();
        dataHandler.SetLoopBracketsMap(preprocessor.PreprocessInput("++++>[..[..].]>---", factory));
        Assertions.assertEquals(13, dataHandler.GetClosingBracketIndex(5));
        Assertions.assertEquals(11, dataHandler.GetClosingBracketIndex(8));
        Assertions.assertEquals(8, dataHandler.GetOpeningBracketIndex(11));
        Assertions.assertEquals(5, dataHandler.GetOpeningBracketIndex(13));
    }
}
