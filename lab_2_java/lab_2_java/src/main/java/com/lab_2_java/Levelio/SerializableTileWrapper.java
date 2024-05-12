package com.lab_2_java.Levelio;

public class SerializableTileWrapper {
    private String name;
    private String type;

    private String boosterName;

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }
    public String getBoosterName() {
        return boosterName;
    }

    public SerializableTileWrapper(String name, String type, String boosterName) {
        this.name = name;
        this.type = type;
        this.boosterName = boosterName;
    }

    public SerializableTileWrapper() {}
}
