package Source;

import Operations.OperationFactory;

public class BrainFuck{
    private final DataHandler dataHandler = new DataHandler();
    private final Interpreter interpreter = new Interpreter();
    private final IOHandler IOhandler = new IOHandler();

    private final OperationFactory factory = new OperationFactory();

    void Work(){
        while(true) {
            IOhandler.ReadLine();
            String input = IOhandler.GetLine();
            if(input.equals("quit")) break;
            dataHandler.SetLoopBracketsMap(interpreter.Preprocess(input));
            interpreter.Interpret(dataHandler, IOhandler, factory);
        }
    }
}