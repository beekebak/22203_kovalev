package Operations;

import Exceptions.ConfigFileException;
import Exceptions.FactoryException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Properties;


/**
 * Factory that creates operation objects
 * to use them in interpreter.
 */
public class OperationFactory {
    private static final Logger log = LogManager.getLogger("OperationFactory.class.getName()");
    private final HashMap<String, Constructor<? extends Operation>> constructorHashMap = new HashMap<>();

    /**
     * Creates factory.
     * Needs valid configuration file in project resources
     * folder with operations and their classes.
     * File line should look like
     * <code>op = java.class.op</code>
     * where op is operator character
     * java.class.op operator class path.
     * @throws ConfigFileException in case there is no valid configuration file.
     */
    public OperationFactory(String path) throws ConfigFileException {
        ClassLoader loader = getClass().getClassLoader();
        try(InputStream stream = loader.getResourceAsStream(path)){
            Properties property = new Properties();
            property.load(stream);
            for(String key: property.stringPropertyNames()){
                constructorHashMap.put(key, (Constructor<? extends Operation>)
                        Class.forName(property.getProperty(key)).getConstructor(null));
                log.debug("Added new key \"{}\".", key);
            }
            log.info("Factory configured successfully.");
        }
        catch(IOException e){
            log.error("Cant open config file");
            throw new ConfigFileException("Can't open Operations.txt file.");
        }
        catch(ClassNotFoundException | NoSuchMethodException | NullPointerException ex){
            log.error( "Cant open config file");
            throw new ConfigFileException("Can't make factory using provided Operations.txt file.");
        }
    }

    public OperationFactory() throws ConfigFileException {
        this("Operations.txt");
    }

    /**
     * Makes new operation using its class name
     * @param className operation related class name used in configuration file
     * @return new operation instance
     */
    public Operation GetInstance(String className){
        try {
            return constructorHashMap.get(className).newInstance();
        }
        catch (InvocationTargetException | InstantiationException | IllegalAccessException | NullPointerException e) {
            throw new FactoryException("Creating a new operation failed");
        }
    }
}
