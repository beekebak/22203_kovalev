package Operations;

interface Operation{
    abstract void Operate(DataHandler dataHandler, IOHandler IOhandler);
}

//stands for "-"
class Decrement implements Operation{
    public void Operate(byte[] data, int dataPointer){
        data[dataPointer]--;
    }
}

//stands for ">"
class RightShift implements Operation{
    public void Operate(byte[] data, int dataPointer){
        dataPointer++;
    }
}

//stands for "<"
class LeftShift implements Operation{
    public void Operate(byte[] data, int dataPointer){
        dataPointer--;
    }
}

//stands for "."
class DataGetter implements Operation{

}

//stand for ","
class DataSetter implements Operation{

}

//stands for "["
class CycleStart implements Operation{

}

//stands for "]"
class CycleEnd implements Operation{

}