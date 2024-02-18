
public class BrainFuck{
    private DataHandler dataHandler = new DataHandler();
    private Interpreter interpreter = new Interpreter();
    private IOHandler IOhandler = new IOHandler();

    void Work(){
        while(true) {
            String input = IOhandler.ReadLine();
            if(input.equals("quit")) break;
            dataHandler.SetLoopBracketsMap(interpreter.Preprocess(input));
            interpreter.Interpret(input, dataHandler, IOhandler);
        }
    }
}