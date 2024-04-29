package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.scene.image.Image;

import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class BombTile extends BreakableTile{
    private static final Timer timer = new Timer();
    private boolean solid = false;

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
    public boolean isSolid() {
        return solid;
    }

    public void MakeSolid(){
        solid = true;
    }
}
