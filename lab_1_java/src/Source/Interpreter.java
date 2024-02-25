package Source;

import Exceptions.InputFormatException;
import Operations.Operation;
import Operations.OperationFactory;

import java.util.ArrayDeque;
import java.util.HashMap;

class Interpreter {

    void Interpret(DataHandler dataHandler, IOHandler IOhandler, OperationFactory factory) throws InputFormatException{
        while(!IOhandler.StringIsOver()){
            Operation op = factory.GetInstance(String.valueOf(IOhandler.GetChar()));
            if(op == null) throw new InputFormatException("Unsupported operation.");
            op.Operate(dataHandler, IOhandler);
        }
    }
}
