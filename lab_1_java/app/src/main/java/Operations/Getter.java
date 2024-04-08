package Operations;

import Source.ExecutionContext;
import Source.IOHandler;

class Getter implements Operation{
    public Getter(){}
    @Override
    public void Operate(ExecutionContext context, IOHandler IOhandler){
        IOhandler.Write(context.GetData());
    }
    @Override
    public OperationType GetType(){
        return OperationType.DEFAULT_TYPE;
    }
}
