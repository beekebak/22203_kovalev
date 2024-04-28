package com.lab_2_java.Levelio;

import java.util.List;

public class SerializableLevel {
    private List<List<String>> grid;

    public List<List<String>> getGrid() {
        return grid;
    }

    public SerializableLevel(List<List<String>> grid) {
        this.grid = grid;
    }
    public SerializableLevel() {}
}
