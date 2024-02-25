package Source;

import Exceptions.FactoryException;
import Exceptions.InputFormatException;
import Operations.Operation;
import Operations.OperationFactory;

import java.util.ArrayDeque;
import java.util.HashMap;

public class Preprocessor {
    HashMap<Integer, Integer> PreprocessInput(String input, OperationFactory factory) throws InputFormatException {
        HashMap<Integer, Integer> bracketsMap = new HashMap<>();
        ArrayDeque<Integer> openBracketIndexes = new ArrayDeque<Integer>();
        for(int i = 0; i < input.length(); i++){
            try{
                Operation op = factory.GetInstance(String.valueOf(input.charAt(i)));
                if(op.GetType() == Operation.OperationType.CYCLE_START){
                    openBracketIndexes.push(i);
                }
                else if(op.GetType() == Operation.OperationType.CYCLE_END){
                    if(openBracketIndexes.isEmpty()) throw new InputFormatException("Closing bracket before opening.");
                    bracketsMap.put(openBracketIndexes.pop(), i);
                }
                else if(op.GetType() == Operation.OperationType.INPUT_OPERATOR){
                    i++; //skipping next character check since its unnecessary
                }
            }
            catch(FactoryException exception){
                throw new InputFormatException("Unexpected character found while preprocessing input.");
            }
        }
        if(!openBracketIndexes.isEmpty()) throw new InputFormatException("Unpaired opening brackets");
        return bracketsMap;
    }
}
