package Source;

import java.util.HashMap;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Handles data needed in program.
 * Provides operations to access data.
 * Data is array of char and pointer to one data cell.
 * There is also map of loop start/end symbols indexes in current
 * interpreting string.
 */
public class ExecutionContext {
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    private char[] data = new char[30000];
    private int dataPointer = 15000;
    private HashMap<Integer, Integer> loopBracketsMap;

    public void SetLoopBracketsMap(HashMap<Integer, Integer> bracketsMap){
        loopBracketsMap = bracketsMap;
    }

    public char GetData() {
        return data[dataPointer];
    }

    public void SetData(char val) throws ArrayStoreException {
        if (val > 255){
            log.error("Value given to set overflowed 255 or underflowed 0");
            throw new ArrayStoreException("Data cell value overflowed");
        }
        log.debug("{} cell is now {}.", dataPointer-15000, val);
        data[dataPointer] = val;
    }

    public int GetDataPointer() {
        log.debug("Got data pointer which is {}", dataPointer-15000);
        return dataPointer;
    }

    public void SetDataPointer(int val) throws IndexOutOfBoundsException {
        if (val < 0 || val >= 30000){
            log.error("Given data pointer value {} is illegal. It should be 0 <= x <= 30000", val);
            throw new IndexOutOfBoundsException("Illegal data pointer value");
        }
        log.debug("Data pointer is now {}", dataPointer-15000);
        dataPointer = val;
    }

    public int GetOpeningBracketIndex(int index){
        int openingBracketIndex = loopBracketsMap.entrySet().stream().filter(entry -> entry.getValue().
                equals(index)).findFirst().get().getKey();
        log.debug("Got opening bracket from index {}", openingBracketIndex+1);
        return openingBracketIndex;
    }

    public int GetClosingBracketIndex(int index){
        log.debug("Got closing bracket from index {}", loopBracketsMap.get(index)+1);
        return loopBracketsMap.get(index);
    }
}
