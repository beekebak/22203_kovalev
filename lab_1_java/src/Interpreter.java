import Exceptions.InputFormatException;

import java.util.ArrayDeque;
import java.util.HashMap;

class Interpreter {
    HashMap<Integer, Integer> Preprocess(String input) throws InputFormatException {
        HashMap<Integer, Integer> bracketsMap = new HashMap<>();
        ArrayDeque<Integer> openBracketIndexes = new ArrayDeque<Integer>();
        for(int i = 0; i < input.length(); i++){
            if(input.charAt(i) == '['){
                openBracketIndexes.push(i);
            }
            else if(input.charAt(i) == ']'){
                if(openBracketIndexes.isEmpty()) throw new InputFormatException("closing bracket before opening.");
                bracketsMap.put(openBracketIndexes.pop(), i);
            }
        }
        if(!openBracketIndexes.isEmpty()) throw new InputFormatException("unpaired opening brackets");
        return bracketsMap;
    }

    void Interpret(String input, DataHandler dataHandler, IOHandler IOhandler){

    }
}
