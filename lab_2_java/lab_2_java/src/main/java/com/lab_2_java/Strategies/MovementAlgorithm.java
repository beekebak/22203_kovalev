package com.lab_2_java.Strategies;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Utility.MoveDirections;
import com.lab_2_java.Utility.SolidityType;

public abstract class MovementAlgorithm {
    protected MoveDirections direction = MoveDirections.LEFT;

    MoveDirections getDirection() {
        return direction;
    }

    void setDirection(MoveDirections direction) {
        this.direction = direction;
    }

    protected int GetDx(Enemy creature){
        int dx = 0;
        int speed = creature.getSpeed();
        switch (direction) {
            case LEFT -> dx= -speed;
            case RIGHT -> dx = speed;
        }
        return dx;
    }
    protected int GetDy(Enemy creature){
        int dy = 0;
        int speed = creature.getSpeed();
        switch (direction) {
            case UP -> dy = -speed;
            case DOWN -> dy = speed;
        }
        return dy;
    }

    public abstract void MoveImplementation(Enemy creature, SolidityType type);
}
