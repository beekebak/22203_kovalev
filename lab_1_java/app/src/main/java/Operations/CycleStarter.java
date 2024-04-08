package Operations;

import Source.DataHandler;
import Source.IOHandler;

class CycleStarter implements Operation{
    public CycleStarter(){}
    @Override
    public void Operate(DataHandler dataHandler, IOHandler IOhandler){
        if(dataHandler.GetData() == 0){
            IOhandler.SetIter(dataHandler.GetClosingBracketIndex(IOhandler.GetIter()-1)+1);
        }
    }
    @Override
    public OperationType GetType(){
        return OperationType.CYCLE_START;
    }
}
