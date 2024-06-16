package com.lab_2_java.Entities.Tiles.Boosters;

import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Models.GameLevel;
import com.lab_2_java.CollisionHandlers.SolidityType;
import javafx.scene.image.Image;
import javafx.util.Callback;

public class Exit extends Booster {
    private boolean isOpened = false;
    private SolidityType isSolid = SolidityType.SOFT;
    private final Callback<Void, Void> endLevel = new GameLevel.LevelWinEnder();
    public void setOpened(boolean opened){
        isSolid = SolidityType.PERVIOUS;
        isOpened = opened;
    }
    @Override
    public void HandleCollision(Entity collided){
        if(collided instanceof Bomberman) Boost((Bomberman) collided);
    }
    @Override
    public void Boost(Bomberman bomberman){
        if(isOpened){
            DestroySelf();
            endLevel.call(null);
        }
    }
    @Override
    public SolidityType getSolidity(){
        return isSolid;
    }
    public Exit(){
        super.sprite = new Image("/sprites/Exit.png");
    }
}
