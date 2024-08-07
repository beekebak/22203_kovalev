package Operations;

import Source.ExecutionContext;
import Source.IOHandler;

class Decrement implements Operation{
    public Decrement(){}
    @Override
    public void Operate(ExecutionContext context, IOHandler IOhandler){
        context.SetData((char) (context.GetData() - 1));
    }
    @Override
    public OperationType GetType(){
        return OperationType.DEFAULT_TYPE;
    }
}
