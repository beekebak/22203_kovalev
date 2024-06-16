package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Strategies.MovementAlgorithm;
import com.lab_2_java.Strategies.SimpleMovementAlgorithmByCellWrapper;
import com.lab_2_java.Utility.CoordinatesConverter;
import com.lab_2_java.CollisionHandlers.SolidityType;
import javafx.application.Platform;
import javafx.scene.image.Image;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

public class Ogre extends Enemy{
    private final MovementAlgorithm movementStrategy;
    {
        Random random = new Random();
        int changeDirectionFrequency = random.nextInt(1,5);
        movementStrategy = new SimpleMovementAlgorithmByCellWrapper(
                CoordinatesConverter.getCellSize()/speed*changeDirectionFrequency);
    }
    private static final Timer timer = new Timer();
    private final Image sprite = new Image("/sprites/ogre.png");
    private int livesCount = 2;

    private boolean isUnkillable = false;

    public Ogre(int xCoord, int yCoord){
        super(4, xCoord, yCoord);
        super.xSize = CoordinatesConverter.getCellSize()/2-2;
        super.ySize = CoordinatesConverter.getCellSize()/2-2;
        super.centerXShift = CoordinatesConverter.getCellSize()/2;
        super.centerYShift = CoordinatesConverter.getCellSize()/2;
    }

    @Override
    public void Move(){
        movementStrategy.MoveImplementation(this, SolidityType.PERVIOUS);
    }

    @Override
    public Image getSprite() {
        return sprite;
    }

    private void MakeKillable(){
        isUnkillable = false;
    }

    @Override
    protected void DestroySelf(){
        if(isUnkillable) return;
        if(livesCount > 0) {
            livesCount--;
            isUnkillable = true;
            speed = getSpeed()*2;
            TimerTask awaitExplosion = new TimerTask() {
                @Override
                public void run() {
                    Platform.runLater(() -> {MakeKillable();});
                }
            };
            timer.schedule(awaitExplosion, 2000L);
        }
        else{
            super.DestroySelf();
        }
    }
}
