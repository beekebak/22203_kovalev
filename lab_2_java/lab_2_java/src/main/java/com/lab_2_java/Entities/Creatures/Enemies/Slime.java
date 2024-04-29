package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Utility.MoveDirections;
import com.lab_2_java.Utility.SolidCollisionChecker;
import javafx.scene.image.Image;

import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class Slime extends Enemy{
    private final Image sprite = new Image("/sprites/slime.png");
    public Slime(int xCoord, int yCoord){
        super(4, xCoord, yCoord);
        super.xSize = 22;
        super.ySize = 22;
        super.centerXShift = 24;
        super.centerYShift = 24;
    }
    MoveDirections direction = MoveDirections.LEFT;

    private int GetDx(){
        int dx = 0;
        switch (direction) {
            case LEFT -> dx= -speed;
            case RIGHT -> dx = speed;
        }
        return dx;
    }
    private int GetDy(){
        int dy = 0;
        switch (direction) {
            case UP -> dy = -speed;
            case DOWN -> dy = speed;
        }
        return dy;
    }

    @Override
    public void Move(){
        int dx = GetDx();
        int dy = GetDy();
        if(SolidCollisionChecker.CheckMoveValidity(this, dx, dy)) {
            setX(getXValue() + dx);
            setY(getYValue() + dy);
        }
        else{
            List<MoveDirections> directions = Arrays.asList(MoveDirections.values());
            Random random = new Random();
            int idx = random.nextInt(0,4);
            for(int i = 0; i < 4; i++){
                direction = directions.get((idx+i)%4);
                dx = GetDx();
                dy = GetDy();
                if(SolidCollisionChecker.CheckMoveValidity(this, dx, dy)){
                    setX(getXValue() + dx);
                    setY(getYValue() + dy);
                    return;
                }
            }
        }
    }

    @Override
    public Image getSprite() {
        return sprite;
    }
}
