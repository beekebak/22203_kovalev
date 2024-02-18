package Operations;

import Source.DataHandler;
import Source.IOHandler;

class CycleEnder implements Operation{
    public CycleEnder(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        if(dataHandler.GetData() != 0){
            IOhandler.SetIter(dataHandler.GetOpeningBracketIndex(IOhandler.GetIter()-1));
        }
    }
}
