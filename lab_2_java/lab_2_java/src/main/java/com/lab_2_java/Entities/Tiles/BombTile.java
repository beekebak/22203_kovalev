package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.Boosters.ExplosionTile;
import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.scene.image.Image;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class BombTile extends BreakableTile{
    private static final ExecutorService executor = Executors.newSingleThreadExecutor();

    public BombTile(){
        super.sprite = new Image("/sprites/bomb.png");
        Task<Void> awaitExplosion = new Task<Void>() {
            @Override
            public Void call() throws Exception {
                try{
                    Thread.sleep(3000);

                    Platform.runLater(() -> {DestroySelf();});
                }
                catch (InterruptedException e) {}
                return null;
            }
        };
        executor.submit(awaitExplosion);
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
        return false;
    }
}
