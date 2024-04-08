package Operations;

import Source.ExecutionContext;
import Source.IOHandler;

class Setter implements Operation{
    public Setter(){}
    @Override
    public void Operate(ExecutionContext context, IOHandler IOhandler){
        context.SetData(IOhandler.GetChar());
    }
    @Override
    public OperationType GetType(){
        return OperationType.INPUT_OPERATOR;
    }
}

