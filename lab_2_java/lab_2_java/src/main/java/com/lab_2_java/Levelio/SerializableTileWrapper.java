package com.lab_2_java.Levelio;

public class SerializableTileWrapper {
    private int x;
    private int y;
    private String name;

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public String getName() {
        return name;
    }
    public SerializableTileWrapper(int x, int y, String name) {
        this.x = x;
        this.y = y;
        this.name = name;
    }
    public SerializableTileWrapper() {}
}
