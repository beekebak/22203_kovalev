package Operations;

import Source.ExecutionContext;
import Source.IOHandler;

class LeftShift implements Operation{
    public LeftShift(){}
    @Override
    public void Operate(ExecutionContext context, IOHandler IOhandler){
        context.SetDataPointer( context.GetDataPointer() - 1);
    }
    @Override
    public OperationType GetType(){
        return OperationType.DEFAULT_TYPE;
    }
}
