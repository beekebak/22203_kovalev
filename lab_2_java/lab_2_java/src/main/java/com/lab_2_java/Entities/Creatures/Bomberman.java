package com.lab_2_java.Entities.Creatures;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Utility.SolidCollisionChecker;
import com.lab_2_java.Utility.MoveDirections;
import javafx.scene.image.Image;

public class Bomberman extends Creature {
    private final Image sprite = new Image("/sprites/bomberman.png");
    private int bombCount = 1;
    private int bombPower = 1;

    public Bomberman(){
        super(8, new SolidCollisionChecker(), 150, 150);
        super.xSize = 12;
        super.ySize = 18;
        super.centerXShift = 16;
        super.centerYShift = 22;
    }

    public Image getSprite(){
        return sprite;
    }

    public void Move(){}

    public void Move(MoveDirections direction){
        int dx=0, dy=0;
        switch (direction) {
            case UP -> dy = -getSpeed();
            case DOWN -> dy = getSpeed();
            case LEFT -> dx = -getSpeed();
            case RIGHT -> dx = getSpeed();
        }
        if(collisionChecker.CheckMoveValidity(this, dx, dy)) {
            setX(getXValue() + dx);
            setY(getYValue() + dy);
        }
        else while(collisionChecker.CheckMoveValidity(this, dx/4, dy/4)) {
            setX(getXValue() + dx/4);
            setY(getYValue() + dy/4);
        }
    }

    public void HandleCollision(Entity collided) {
        if(collided instanceof Enemy){
            DestroySelf();
        }
    }
}
