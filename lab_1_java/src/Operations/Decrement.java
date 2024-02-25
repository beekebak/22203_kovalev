package Operations;

import Source.DataHandler;
import Source.IOHandler;

//stands for "+"
class Decrement implements Operation{
    public Decrement(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        dataHandler.SetData((char) (dataHandler.GetData() - 1));
    }
    @Override
    public OperationType GetType(){
        return OperationType.DEFAULT_TYPE;
    }
}
