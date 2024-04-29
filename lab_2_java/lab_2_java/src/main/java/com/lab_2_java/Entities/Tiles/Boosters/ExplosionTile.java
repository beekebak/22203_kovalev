package com.lab_2_java.Entities.Tiles.Boosters;

import com.lab_2_java.Entities.Tiles.UnbreakableTile;
import javafx.scene.image.Image;

public class ExplosionTile extends UnbreakableTile {
    public ExplosionTile(){
        super.sprite = new Image("/sprites/explosion.png");
    }

    @Override
    public boolean isSolid() {
        return false;
    }
}
