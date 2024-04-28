package com.lab_2_java.Utility;

public abstract class CoordinatesConverter {
    public static int ConvertGridCoordinateToViewCoordinate(int coordinate){
        return coordinate*48;
    }
    public static int CenterViewCoordinate(int coordinate){
        return coordinate/48*48+24;
    }
    public static int ConvertViewCoordinateToGridCoordinate(int coordinate){
        return coordinate/48;
    }
}
