package com.lab_2_java.Strategies;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Utility.SolidityType;

public class ProxySimpleAlgorithm extends MovementAlgorithm{
    private final SimpleMovementAlgorithmByCellWrapper algorithm;

    ProxySimpleAlgorithm(int repeats){
        algorithm = new SimpleMovementAlgorithmByCellWrapper(repeats);
    }

    @Override
    public void MoveImplementation(Enemy creature, SolidityType type){
        algorithm.MoveImplementation(creature, type);
    }

    public boolean Done(){
        return algorithm.getCurrentRepeats() % algorithm.getRepeats() == 0;
    }
}
