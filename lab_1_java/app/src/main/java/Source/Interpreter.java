package Source;

import Exceptions.InputFormatException;
import Operations.Operation;
import Operations.OperationFactory;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Interprets and executes every character from input string.
 */
class Interpreter {
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    /**
     * Interprets program line.
     * @param context Handles input data and special operations data structures if needed.
     * @param IOhandler provides needed I/O operations.
     * @param factory factory that creates new operation instances.
     * @throws InputFormatException thrown in case invalid symbol provided.
     * Should never throw in this realisation because string is already checked
     * during preprocessing.
     */
     void Interpret(ExecutionContext context, IOHandler IOhandler, OperationFactory factory) throws InputFormatException{
        while(!IOhandler.StringIsOver()){
            Operation op = factory.GetInstance(String.valueOf(IOhandler.GetChar()));
            if(op == null){
                log.error("Unsupported operation character in input string");
                throw new InputFormatException("Unsupported operation.");
            }
            op.Operate(context, IOhandler);
        }
    }
}
