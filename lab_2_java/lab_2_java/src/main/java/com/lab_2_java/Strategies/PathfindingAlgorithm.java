package com.lab_2_java.Strategies;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Algorithms.PathInfo;
import com.lab_2_java.CollisionHandlers.SolidityType;

public class PathfindingAlgorithm extends MovementAlgorithm {
    protected int repeats;
    protected int currentRepeat = 0;

    public PathfindingAlgorithm(int repeats){
        this.repeats = repeats;
    }

    public int getRepeats() {
        return repeats;
    }

    public int getCurrentRepeat() {
        return currentRepeat;
    }

    @Override
    public void MoveImplementation(Enemy creature, SolidityType type){
        if(currentRepeat % repeats == 0) {
            PathInfo info = com.lab_2_java.Algorithms.PathfindingAlgorithm.GetRangeToBomberman(creature, type);
            direction = info.firstStepDirection;
            currentRepeat = 0;
        }
        int dx = GetDx(creature);
        int dy = GetDy(creature);
        creature.setY(creature.getYValue()+dy);
        creature.setX(creature.getXValue()+dx);
        currentRepeat++;
    }
}
