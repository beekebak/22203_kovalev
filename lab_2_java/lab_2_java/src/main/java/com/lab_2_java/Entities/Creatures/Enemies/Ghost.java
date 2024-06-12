package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Strategies.PathfindingAlgorithm;
import com.lab_2_java.Strategies.MovementAlgorithm;
import com.lab_2_java.Utility.CoordinatesConverter;
import com.lab_2_java.Utility.SolidityType;
import javafx.scene.image.Image;

public class Ghost extends Enemy{
    private final MovementAlgorithm movementStrategy = new PathfindingAlgorithm(
            CoordinatesConverter.getCellSize()/speed);
    private final Image sprite = new Image("/sprites/ghost.png");

    public Ghost(int xCoord, int yCoord){
        super(2, xCoord, yCoord);
        super.xSize = CoordinatesConverter.getCellSize()/2-2;
        super.ySize = CoordinatesConverter.getCellSize()/2-2;
        super.centerXShift = CoordinatesConverter.getCellSize()/2;
        super.centerYShift = CoordinatesConverter.getCellSize()/2;
    }

    @Override
    public void Move(){
        movementStrategy.MoveImplementation(this, SolidityType.SOFT);
    }

    @Override
    public Image getSprite() {
        return sprite;
    }
}
