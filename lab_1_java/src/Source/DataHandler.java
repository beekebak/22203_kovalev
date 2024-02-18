package Source;

import java.util.HashMap;

public class DataHandler {
    private char[] data = new char[30000];
    private int dataPointer = 15000;
    private HashMap<Integer, Integer> loopBracketsMap;

    public char GetData() {
        return data[dataPointer];
    }

    public void SetData(char val) throws ArrayStoreException {
        if (val > 255) throw new ArrayStoreException("Data cell value overflowed");
        data[dataPointer] = val;
    }

    public int GetDataPointer() {
        return dataPointer;
    }

    public void SetDataPointer(int val) throws IndexOutOfBoundsException {
        if (val < 0 || val >= 30000) throw new IndexOutOfBoundsException("Illegal data pointer value");
        dataPointer = val;
    }

    public int GetOpeningBracketIndex(int index){
        return loopBracketsMap.entrySet().stream().filter(entry -> entry.getValue().
                                equals(index)).findFirst().get().getKey();
    }

    public int GetClosingBracketIndex(int index){
        return loopBracketsMap.get(index);
    }

    void SetLoopBracketsMap(HashMap<Integer, Integer> bracketsMap){
        loopBracketsMap = bracketsMap;
    }
}
