package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Utility.SolidityType;
import javafx.scene.image.Image;

public class BreakableTile extends Tile {
    protected boolean isInvincible = false;
    private BreakableTile underlyingTile = null;

    public BreakableTile getUnderlyingTile() {
        return underlyingTile;
    }

    public void setUnderlyingTile(BreakableTile underlyingTile) {
        this.underlyingTile = underlyingTile;
    }

    public BreakableTile(){
        sprite = new Image("/sprites/box.png");
    }

    @Override
    public void HandleCollision(Entity collided) {
        if(collided instanceof ExplosionTile && !isInvincible){
            DestroySelf();
        }
    }
    protected void DestroySelf(){
        isBroken.set(true);
    }

    @Override
    public SolidityType getSolidity() {
        return SolidityType.SOFT;
    }
}
