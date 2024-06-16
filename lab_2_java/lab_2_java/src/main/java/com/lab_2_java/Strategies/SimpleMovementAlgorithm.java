package com.lab_2_java.Strategies;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Utility.MoveDirections;
import com.lab_2_java.CollisionHandlers.SolidCollisionChecker;
import com.lab_2_java.CollisionHandlers.SolidityType;

import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class SimpleMovementAlgorithm extends MovementAlgorithm {

    @Override
    public void MoveImplementation(Enemy creature, SolidityType type){
        int dx = GetDx(creature);
        int dy = GetDy(creature);
        if(SolidCollisionChecker.CheckMoveValidity(creature, dx, dy, type)) {
            creature.setX(creature.getXValue() + dx);
            creature.setY(creature.getYValue() + dy);
        }
        else{
            List<MoveDirections> directions = Arrays.asList(MoveDirections.values());
            Random random = new Random();
            int idx = random.nextInt(0,4);
            for(int i = 0; i < 4; i++){
                direction = directions.get((idx+i)%4);
                dx = GetDx(creature);
                dy = GetDy(creature);
                if(SolidCollisionChecker.CheckMoveValidity(creature, dx, dy, type)){
                    creature.setX(creature.getXValue() + dx);
                    creature.setY(creature.getYValue() + dy);
                    return;
                }
            }
        }
    }
}
