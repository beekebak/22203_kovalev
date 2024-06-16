package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.CollisionHandlers.SolidityType;
import javafx.application.Platform;
import javafx.scene.image.Image;

import java.util.Timer;
import java.util.TimerTask;

public class BombTile extends BreakableTile{
    private static final Timer timer = new Timer();
    private SolidityType solid = SolidityType.PERVIOUS;

    public BombTile(){
        super.sprite = new Image("/sprites/bomb.png");
        TimerTask awaitExplosion = new TimerTask() {
            @Override
            public void run() {
                Platform.runLater(() -> {DestroySelf();});
            }
        };
        timer.schedule(awaitExplosion, 3000L);
    }
    @Override
    public void HandleCollision(Entity collided) {
        if(collided instanceof ExplosionTile){
            DestroySelf();
        }
    }
    protected void DestroySelf(){
        super.DestroySelf();
    }

    @Override
    public SolidityType getSolidity() {
        return solid;
    }

    public void MakeSolid(){
        solid = SolidityType.SOFT;
    }
}
