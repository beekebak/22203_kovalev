package Operations;

import Source.DataHandler;
import Source.IOHandler;

/**
 * Provides interface needed for any operation
 * to be interpreted.
 */
public interface Operation{
    public enum OperationType{
        CYCLE_START,
        CYCLE_END,
        INPUT_OPERATOR,
        DEFAULT_TYPE
    }
    void Operate(DataHandler dataHandler, IOHandler IOhandler);
    OperationType GetType();
}