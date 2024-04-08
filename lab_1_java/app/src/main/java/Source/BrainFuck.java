package Source;

import Operations.OperationFactory;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Brainfuck interpreter class
 */
public class BrainFuck{
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    private final DataHandler dataHandler = new DataHandler();
    private final Interpreter interpreter = new Interpreter();
    private final Preprocessor preprocessor = new Preprocessor();
    private final IOHandler IOhandler = new IOHandler();

    private final OperationFactory factory = new OperationFactory();

    /**
     * Infinite loop in which interpreter works.
     */
    public void Work(){
        try {
            while (true) {
                IOhandler.ReadLine();
                String input = IOhandler.GetLine();
                if (input.equals("quit")){
                    log.info("Program ended successfully.");
                    break;
                }
                dataHandler.SetLoopBracketsMap(preprocessor.PreprocessInput(input, factory));
                interpreter.Interpret(dataHandler, IOhandler, factory);
            }
        }
        catch (RuntimeException exception){
            try{
                IOhandler.Write("Exception occurred during program run. Check log file for more details.");
            }
            catch(RuntimeException ex){
                log.error("Error occurred during I/O operation.");
            }
        }
    }
}