package com.lab_2_java.Strategies;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.CollisionHandlers.SolidityType;

public class ProxyPathfindingAlgorithm extends MovementAlgorithm{
    private final PathfindingAlgorithm algorithm;

    ProxyPathfindingAlgorithm(int repeats){
        algorithm = new PathfindingAlgorithm(repeats);
    }

    @Override
    public void MoveImplementation(Enemy creature, SolidityType type){
        algorithm.MoveImplementation(creature, type);
    }

    public boolean Done(){
        return algorithm.getCurrentRepeat() % algorithm.getRepeats() == 0;
    }
}
