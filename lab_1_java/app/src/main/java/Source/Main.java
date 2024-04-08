package Source;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Main entry
 */
public class Main {
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    public static void main(String[] args) {
        BrainFuck brainFuck = new BrainFuck();
        log.info("Program started.");
        brainFuck.Work();
    }
}