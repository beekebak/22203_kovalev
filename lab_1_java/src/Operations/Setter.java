package Operations;

import Source.DataHandler;
import Source.IOHandler;

//stands for "+"
class Setter implements Operation{
    public Setter(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        dataHandler.SetData(IOhandler.GetChar());
    }
}

