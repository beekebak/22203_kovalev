package com.lab_2_java.Entities;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Properties;


public class EntityFactory<T extends Entity> {
    private final HashMap<String, Constructor<T>> constructorHashMap = new HashMap<>();

    public EntityFactory(String path, Class<?>... parameterTypes) throws RuntimeException {
        ClassLoader loader = getClass().getClassLoader();
        try(InputStream stream = loader.getResourceAsStream(path)){
            Properties property = new Properties();
            property.load(stream);
            for(String key: property.stringPropertyNames()){
                constructorHashMap.put(key, (Constructor<T>)
                        Class.forName(property.getProperty(key)).getConstructor(parameterTypes));
            }
        }
        catch(IOException e){
            throw new RuntimeException("Can't open Operations.txt file.");
        }
        catch(ClassNotFoundException | NoSuchMethodException | NullPointerException ex){
            throw new RuntimeException("Can't make factory using provided Operations.txt file.");
        }
    }

    public T GetInstance(String className){
        try {
            return  constructorHashMap.get(className).newInstance();
        }
        catch (InvocationTargetException | InstantiationException | IllegalAccessException | NullPointerException e) {
            throw new RuntimeException("Creating a new entity failed");
        }
    }
}