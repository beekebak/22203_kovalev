package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Utility.SolidityType;
import javafx.scene.image.Image;

public class UnbreakableTile extends Tile{
    public UnbreakableTile(){
        sprite = new Image("/sprites/MetalBox.png");
    }
    @Override
    public void HandleCollision(Entity collided) {}

    @Override
    public SolidityType getSolidity() {
        return SolidityType.HARD;
    }
}
