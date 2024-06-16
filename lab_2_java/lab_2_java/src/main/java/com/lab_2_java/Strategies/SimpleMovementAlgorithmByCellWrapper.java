package com.lab_2_java.Strategies;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Utility.MoveDirections;
import com.lab_2_java.CollisionHandlers.SolidityType;

import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class SimpleMovementAlgorithmByCellWrapper extends MovementAlgorithm{
    SimpleMovementAlgorithm algorithm = new SimpleMovementAlgorithm();
    int repeats;
    int currentRepeats = 0;
    public SimpleMovementAlgorithmByCellWrapper(int repeats){
        this.repeats = repeats;
    }

    public int getRepeats() {
        return repeats;
    }

    public int getCurrentRepeats() {
        return currentRepeats;
    }

    private void ChangeDirection(){
        List<MoveDirections> directions = Arrays.asList(MoveDirections.values());
        Random random = new Random();
        int idx = random.nextInt(0,4);
        algorithm.direction = directions.get(idx);
    }

    @Override
    public void setDirection(MoveDirections direction){
        algorithm.setDirection(direction);
    }

    @Override
    public void MoveImplementation(Enemy creature, SolidityType type) {
        if(currentRepeats % repeats == 0){
            currentRepeats = 0;
            ChangeDirection();
        }
        algorithm.MoveImplementation(creature, type);
        currentRepeats++;
    }
}
