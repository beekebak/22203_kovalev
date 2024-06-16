package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.CollisionHandlers.SolidityType;
import javafx.scene.image.Image;

public class ExplosionTile extends UnbreakableTile {
    public ExplosionTile(){
        super.sprite = new Image("/sprites/explosion.png");
    }

    @Override
    public SolidityType getSolidity() {
        return SolidityType.PERVIOUS;
    }
}
