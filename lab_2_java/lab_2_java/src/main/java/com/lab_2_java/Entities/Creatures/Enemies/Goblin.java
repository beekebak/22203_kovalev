package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Strategies.BombCheckingSimpleStrategy;
import com.lab_2_java.Strategies.MovementAlgorithm;
import com.lab_2_java.Utility.CoordinatesConverter;
import com.lab_2_java.Utility.SolidityType;
import javafx.scene.image.Image;

import java.util.Random;

public class Goblin extends Enemy{
    private static int bombCheckingRadius = 6;
    private final MovementAlgorithm movementStrategy;
    {
        Random random = new Random();
        int changeDirectionFrequency = random.nextInt(0,5);
        movementStrategy = new BombCheckingSimpleStrategy(
            CoordinatesConverter.getCellSize() / speed * 100, bombCheckingRadius);
    }
    private final Image sprite = new Image("/sprites/goblin.png");
    public Goblin(int xCoord, int yCoord){
        super(6, xCoord, yCoord);
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
