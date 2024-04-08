package Source;

import Exceptions.FactoryException;
import Exceptions.InputFormatException;
import Operations.Operation;
import Operations.OperationFactory;

import java.util.ArrayDeque;
import java.util.HashMap;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Preprocessor does work to check input string
 * before it will be interpreted.
 */
public class Preprocessor {
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    /**
     * Checks input validness and resolves cycles.
     * @param input string to be checked.
     * @param factory operation factory to get operation behaviour.
     * @return each cycle start mapped with its end.
     * @throws InputFormatException thrown in case input string is not valid.
     */
    public HashMap<Integer, Integer> PreprocessInput(String input, OperationFactory factory) throws InputFormatException {
        HashMap<Integer, Integer> bracketsMap = new HashMap<>();
        ArrayDeque<Integer> openBracketIndexes = new ArrayDeque<>();
        for(int i = 0; i < input.length(); i++){
            try{
                Operation op = factory.GetInstance(String.valueOf(input.charAt(i)));
                if(op.GetType() == Operation.OperationType.CYCLE_START){
                    openBracketIndexes.push(i);
                    log.debug("Opening bracket found at index {}.", i+1);
                }
                else if(op.GetType() == Operation.OperationType.CYCLE_END){
                    if(openBracketIndexes.isEmpty()) {
                        log.error("Invalid input format: closing bracket before opening.");
                        throw new InputFormatException("Closing bracket before opening.");
                    }
                    log.debug("Opening bracket found at index {} matched opening bracket at{}.",
                            i+1, openBracketIndexes.peek());
                    bracketsMap.put(openBracketIndexes.pop(), i);
                }
                else if(op.GetType() == Operation.OperationType.INPUT_OPERATOR){
                    i++;
                }
            }
            catch(FactoryException exception){
                log.error("Invalid input format: unexpected character found while preprocessing input.");
                throw new InputFormatException("Unexpected character found while preprocessing input.");
            }
        }
        if(!openBracketIndexes.isEmpty()){
            log.error("Invalid input format: unpaired opening bracket found while preprocessing input.");
            throw new InputFormatException("Unpaired opening brackets");
        }
        log.info("Preprocessing success.");
        return bracketsMap;
    }
}
