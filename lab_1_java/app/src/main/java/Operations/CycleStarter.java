package Operations;

import Source.ExecutionContext;
import Source.IOHandler;

class CycleStarter implements Operation{
    public CycleStarter(){}
    @Override
    public void Operate(ExecutionContext context, IOHandler IOhandler){
        if(context.GetData() == 0){
            IOhandler.SetIter(context.GetClosingBracketIndex(IOhandler.GetIter()-1)+1);
        }
    }
    @Override
    public OperationType GetType(){
        return OperationType.CYCLE_START;
    }
}
