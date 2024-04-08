package Operations;

import Source.DataHandler;
import Source.IOHandler;

class LeftShift implements Operation{
    public LeftShift(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        dataHandler.SetDataPointer( dataHandler.GetDataPointer() - 1);
    }
    @Override
    public OperationType GetType(){
        return OperationType.DEFAULT_TYPE;
    }
}
