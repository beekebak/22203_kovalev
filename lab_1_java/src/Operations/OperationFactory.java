package Operations;

import Exceptions.ConfigFileException;
import Exceptions.FactoryException;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Properties;

public class OperationFactory {
    HashMap<String, Constructor<? extends Operation>> constructorHashMap = new HashMap<>();
    public OperationFactory() throws ConfigFileException {
        ClassLoader loader = getClass().getClassLoader();
        try(InputStream stream = loader.getResourceAsStream("Operations.txt")){
            Properties property = new Properties();
            property.load(stream);
            for(String key: property.stringPropertyNames()){
                constructorHashMap.put(key, (Constructor<? extends Operation>)
                        Class.forName(property.getProperty(key)).getConstructor(null));
            }
        }
        catch(IOException e){
            throw new ConfigFileException("Can't open Operations.txt file.");
        }
        catch(ClassNotFoundException | NoSuchMethodException ex){
            throw new ConfigFileException("Can't make factory using provided Operations.txt file.");
        }
    }
     public Operation GetInstance(String className){
        try {
            return constructorHashMap.get(className).newInstance();
        }
        catch (InvocationTargetException | InstantiationException | IllegalAccessException e) {
            throw new FactoryException("Creating a new operation failed");
        }
    }
}
