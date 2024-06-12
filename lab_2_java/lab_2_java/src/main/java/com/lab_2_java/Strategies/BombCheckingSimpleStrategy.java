package com.lab_2_java.Strategies;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Utility.BombLookingAlgorithm;
import com.lab_2_java.Utility.MoveDirections;
import com.lab_2_java.Utility.SolidityType;

public class BombCheckingSimpleStrategy extends MovementAlgorithm {
    private MovementAlgorithm algorithm;
    private int bombCheckingRadius;
    public BombCheckingSimpleStrategy(int repeats, int bombCheckingRadius){
        algorithm = new SimpleMovementAlgorithmByCellWrapper(repeats);
        this.bombCheckingRadius = bombCheckingRadius;
    }

    @Override
    public void MoveImplementation(Enemy creature, SolidityType type) {
        MoveDirections direction = BombLookingAlgorithm.CheckBombs(creature, bombCheckingRadius);
        if(direction != MoveDirections.NONE) {
            algorithm.setDirection(direction);
        }
        algorithm.MoveImplementation(creature, type);
    }
}
