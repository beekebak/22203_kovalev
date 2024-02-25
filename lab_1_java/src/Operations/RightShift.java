package Operations;

import Source.DataHandler;
import Source.IOHandler;

//stands for "+"
class RightShift implements Operation{
    public RightShift(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        dataHandler.SetDataPointer( dataHandler.GetDataPointer() + 1);
    }
    @Override
    public OperationType GetType(){
        return OperationType.DEFAULT_TYPE;
    }
}
