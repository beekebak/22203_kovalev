package com.lab_2_java.Utility;

public abstract class CoordinatesConverter {
    private static int cellSize = 48;
    public static int ConvertGridCoordinateToViewCoordinate(int coordinate){
        return coordinate*cellSize;
    }
    public static int ConvertViewCoordinateToGridCoordinate(int coordinate){
        return coordinate/cellSize;
    }
    public static int getCellSize() {
        return cellSize;
    }
}
