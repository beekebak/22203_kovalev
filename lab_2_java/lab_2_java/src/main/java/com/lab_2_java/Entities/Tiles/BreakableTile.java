package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.Boosters.ExplosionTile;
import javafx.scene.image.Image;

public class BreakableTile extends Tile {
    public BreakableTile(){
        sprite = new Image("/sprites/box.png");
    }

    @Override
    public void HandleCollision(Entity collided) {
        if(collided instanceof ExplosionTile){
            DestroySelf();
        }
    }

    protected void DestroySelf(){
        isBroken.set(true);
    }
}
