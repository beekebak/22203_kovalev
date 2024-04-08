package test;

import Exceptions.ConfigFileException;
import Exceptions.FactoryException;
import Operations.OperationFactory;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class OperationFactoryTest {
    @Test
    public void TestFactoryConstructors(){
        OperationFactory operationFactory = new OperationFactory();
        Assertions.assertThrows(ConfigFileException.class, () -> new OperationFactory("wrong path"));
        OperationFactory operationFactoryByPath = new OperationFactory("Operations.txt");
    }
    @Test
    public void TestGetInstanceFunction(){
        OperationFactory operationFactory = new OperationFactory();
        Assertions.assertThrows(FactoryException.class, () -> operationFactory.GetInstance("?"));
        operationFactory.GetInstance(".");
    }
}
