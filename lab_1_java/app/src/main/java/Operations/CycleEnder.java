package Operations;

import Source.ExecutionContext;
import Source.IOHandler;

class CycleEnder implements Operation{
    public CycleEnder(){}
    @Override
    public void Operate(ExecutionContext context, IOHandler IOhandler){
        if(context.GetData() != 0){
            IOhandler.SetIter(context.GetOpeningBracketIndex(IOhandler.GetIter()-1));
        }
    }
    @Override
    public OperationType GetType(){
        return OperationType.CYCLE_END;
    }
}
