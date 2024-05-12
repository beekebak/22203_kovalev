package com.lab_2_java.Levelio;

import java.util.List;

public class SerializableLevel {
    private List<List<SerializableTileWrapper>> grid;

    public List<List<SerializableTileWrapper>> getGrid() {
        return grid;
    }

    public SerializableLevel(List<List<SerializableTileWrapper>> grid) {
        this.grid = grid;
    }

    public SerializableLevel() {}
}
