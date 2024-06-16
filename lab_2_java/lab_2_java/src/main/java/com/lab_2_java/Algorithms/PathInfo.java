package com.lab_2_java.Algorithms;

import com.lab_2_java.Utility.MoveDirections;

public class PathInfo {
    public int size;
    public MoveDirections firstStepDirection;

    public PathInfo(int size, MoveDirections firstStepDirection) {
        this.size = size;
        this.firstStepDirection = firstStepDirection;
    }
}
