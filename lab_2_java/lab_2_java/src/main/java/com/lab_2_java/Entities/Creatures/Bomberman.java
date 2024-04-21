package com.lab_2_java.Entities.Creatures;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Utility.CollisionChecker;
import com.lab_2_java.Utility.MoveDirections;
import javafx.scene.image.Image;

public class Bomberman extends Creature {
    private Image sprite = new Image("/sprites/bomberman.png");
    int bombsCount = 1;
    int bombPower = 1;

    public Bomberman(){
        super(10, new CollisionChecker(), 100, 100);
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
        setX(getX().get()+dx);
        setY(getY().get()+dy);
    }

    public void HandleCollision(Entity collided) {
        if(collided instanceof Enemy){
            DestroySelf();
        }
    }
}
