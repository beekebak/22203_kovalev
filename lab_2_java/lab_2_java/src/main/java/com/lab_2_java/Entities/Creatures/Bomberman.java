package com.lab_2_java.Entities.Creatures;

import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.BombTile;
import com.lab_2_java.Entities.Tiles.ExplosionTile;
import com.lab_2_java.Utility.SolidCollisionChecker;
import com.lab_2_java.Utility.MoveDirections;
import com.lab_2_java.Utility.SolidityType;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.scene.image.Image;

public class Bomberman extends Creature {
    private final Image sprite = new Image("/sprites/bomberman.png");

    private int bombCount = 1;

    public int getBombCount() {
        return bombCount;
    }

    public void setBombCount(int bombCount) {
        this.bombCount = bombCount;
    }

    private int bombPower = 1;

    public int getBombPower() {
        return bombPower;
    }

    public void setBombPower(int bombPower) {
        this.bombPower = bombPower;
    }

    public Bomberman(int xCoord, int yCoord){
        super(6, xCoord, yCoord);
        super.xSize = 12;
        super.ySize = 18;
        super.centerXShift = 16;
        super.centerYShift = 22;
    }

    public int getSpeed(){
        return speed;
    }

    public void setSpeed(int speed){
        this.speed = speed;
    }

    public Image getSprite(){
        return sprite;
    }

    public void Move(){
        throw new RuntimeException("No move in bomberman");
    }

    public void Move(MoveDirections direction){
        int dx=0, dy=0;
        switch (direction) {
            case UP -> dy = -speed;
            case DOWN -> dy = speed;
            case LEFT -> dx = -speed;
            case RIGHT -> dx = speed;
        }
        if(SolidCollisionChecker.CheckMoveValidity(this, dx, dy, SolidityType.PERVIOUS)) {
            setX(getXValue() + dx);
            setY(getYValue() + dy);
        }
        else while(SolidCollisionChecker.CheckMoveValidity(this, dx/4, dy/4, SolidityType.PERVIOUS)) {
            setX(getXValue() + dx/4);
            setY(getYValue() + dy/4);
        }
    }

    public BombTile PlantBomb(){
        if(bombCount == 0) return null;
        bombCount--;
        BombTile bomb = new BombTile();
        bomb.isBrokenProperty().addListener((observable) -> {
            bombCount++;
        });
        return bomb;
    }

    public void HandleCollision(Entity collided) {
        if(collided instanceof Enemy || collided instanceof ExplosionTile){
            DestroySelf();
        }
    }

    public SimpleBooleanProperty GetProperty(){
        return isAlive;
    }
}
