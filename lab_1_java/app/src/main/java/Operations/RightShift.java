package Operations;

import Source.ExecutionContext;
import Source.IOHandler;

class RightShift implements Operation{
    public RightShift(){}
    @Override
    public void Operate(ExecutionContext context, IOHandler IOhandler){
        context.SetDataPointer( context.GetDataPointer() + 1);
    }
    @Override
    public OperationType GetType(){
        return OperationType.DEFAULT_TYPE;
    }
}
