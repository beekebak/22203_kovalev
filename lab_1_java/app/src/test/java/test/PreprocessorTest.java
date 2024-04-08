package test;

import Exceptions.InputFormatException;
import Operations.OperationFactory;
import Source.Preprocessor;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashMap;

public class PreprocessorTest {
    Preprocessor preprocessor;
    OperationFactory factory = new OperationFactory();
    @BeforeEach
    public void Setup(){
        preprocessor = new Preprocessor();
    }

    @Test
    public void InvalidInput(){
        Assertions.assertThrows(InputFormatException.class, () -> preprocessor.PreprocessInput("?????", factory));
        Assertions.assertThrows(InputFormatException.class, () -> preprocessor.PreprocessInput("....]", factory));
        Assertions.assertThrows(InputFormatException.class, () -> preprocessor.PreprocessInput("....[++++", factory));
    }

    @Test
    public void WorksCorrectly(){
        HashMap<Integer, Integer> hashMap = new HashMap<>();
        hashMap.put(0, 8);
        Assertions.assertEquals(hashMap, preprocessor.PreprocessInput("[+-><.,7]", factory));
    }

}
