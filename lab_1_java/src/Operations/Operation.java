package Operations;

import Source.DataHandler;
import Source.IOHandler;

public interface Operation{
    abstract void Operate(DataHandler dataHandler, IOHandler IOhandler);
}