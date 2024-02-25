package Source;

import Operations.OperationFactory;

public class BrainFuck{
    private final DataHandler dataHandler = new DataHandler();
    private final Interpreter interpreter = new Interpreter();
    private final Preprocessor preprocessor = new Preprocessor();
    private final IOHandler IOhandler = new IOHandler();

    private final OperationFactory factory = new OperationFactory();

    void Work(){
        while(true) {
            IOhandler.ReadLine();
            String input = IOhandler.GetLine();
            if(input.equals("quit")) break;
            dataHandler.SetLoopBracketsMap(preprocessor.PreprocessInput(input, factory));
            interpreter.Interpret(dataHandler, IOhandler, factory);
        }
    }
}