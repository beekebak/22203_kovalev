package com.lab_2_java.Levelio;

public class SerializableTileWrapper {
    public SerializableTileWrapper(String name, String type) {
        this.name = name;
        this.type = type;
    }

    public SerializableTileWrapper() {}

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    private String name;
    private String type;
}
