package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import javafx.scene.image.Image;

import java.security.cert.TrustAnchor;

public class BreakableTile extends Tile {
    public BreakableTile(){
        sprite = new Image("/sprites/box.png");
    }

    @Override
    public void HandleCollision(Entity collided) {}

    private void DestroySelf(){
        isBroken.set(true);
    }
}
