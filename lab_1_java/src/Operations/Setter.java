package Operations;

import Source.DataHandler;
import Source.IOHandler;

class Setter implements Operation{
    public Setter(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        dataHandler.SetData(IOhandler.GetChar());
    }
    @Override
    public OperationType GetType(){
        return OperationType.INPUT_OPERATOR;
    }
}

