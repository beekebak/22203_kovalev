package com.lab_2_java.Utility;

public class PathInfo {
    public int size;
    public MoveDirections firstStepDirection;

    public PathInfo(int size, MoveDirections firstStepDirection) {
        this.size = size;
        this.firstStepDirection = firstStepDirection;
    }
}
