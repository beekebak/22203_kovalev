package com.lab_2_java.Utility;

import javafx.beans.property.SimpleBooleanProperty;
import javafx.scene.image.Image;

public class ObservableConstructorTileWrapper{
    private ConstructorTileWrapper wrapper;
    private SimpleBooleanProperty isNull;
    public ConstructorTileWrapper getWrapper() {
        return wrapper;
    }

    public void setWrapper(ConstructorTileWrapper wrapper) {
        this.wrapper = wrapper;
        if(wrapper == null) isNull.set(true);
        else isNull.set(false);
    }

    public SimpleBooleanProperty IsNullProperty() {
        return isNull;
    }

    public boolean IsNullValue(){
        return isNull.get();
    }

    public ObservableConstructorTileWrapper(String name, String typeName, Image image) {
        wrapper = new ConstructorTileWrapper(name, typeName, image);
        isNull = new SimpleBooleanProperty(false);
    }
    public ObservableConstructorTileWrapper(ConstructorTileWrapper wrapper){
        this.wrapper = wrapper;
        isNull = new SimpleBooleanProperty(false);
    }
}
