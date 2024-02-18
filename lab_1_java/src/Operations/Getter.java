package Operations;

import Source.DataHandler;
import Source.IOHandler;

class Getter implements Operation{
    public Getter(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        IOhandler.Write(dataHandler.GetData());
    }
}
