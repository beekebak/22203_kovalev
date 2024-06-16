package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Strategies.LimitedPathfindingAlgorithm;
import com.lab_2_java.Strategies.MovementAlgorithm;
import com.lab_2_java.Utility.CoordinatesConverter;
import com.lab_2_java.CollisionHandlers.SolidityType;
import javafx.scene.image.Image;

public class Dragon extends Enemy{
    private static final int visionLength = 5;
    private final MovementAlgorithm movementStrategy = new LimitedPathfindingAlgorithm(
            CoordinatesConverter.getCellSize()/speed, visionLength);
    private final Image sprite = new Image("/sprites/dragon.webp");

    public Dragon(int xCoord, int yCoord){
        super(8, xCoord, yCoord);
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
}
