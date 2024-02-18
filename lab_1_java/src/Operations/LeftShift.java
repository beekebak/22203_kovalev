package Operations;

import Source.DataHandler;
import Source.IOHandler;

//stands for "+"
class LeftShift implements Operation{
    public LeftShift(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        dataHandler.SetDataPointer( dataHandler.GetDataPointer() - 1);
    }
}
