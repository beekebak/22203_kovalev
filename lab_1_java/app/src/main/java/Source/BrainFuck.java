package Source;

import Operations.OperationFactory;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.*;

/**
 * Brainfuck interpreter
 * Executes infinite loop in which program works
 */
public class BrainFuck{
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    private final ExecutionContext context = new ExecutionContext();
    private final Interpreter interpreter = new Interpreter();
    private final Preprocessor preprocessor = new Preprocessor();
    private final IOHandler IOhandler;
    private final OperationFactory factory = new OperationFactory();

    public BrainFuck(InputStream in, OutputStream out){
        IOhandler = new IOHandler(in, out);
    }
    public BrainFuck(){
        IOhandler = new IOHandler();
    }

    public void Work(){
        try {
            while (true) {
                IOhandler.ReadLine();
                String input = IOhandler.GetLine();
                if (input.equals("quit")){
                    log.info("Program ended successfully.");
                    break;
                }
                context.SetLoopBracketsMap(preprocessor.PreprocessInput(input, factory));
                interpreter.Interpret(context, IOhandler, factory);
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