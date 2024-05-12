package com.lab_2_java.Entities.Tiles.Boosters;

import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Entities.Tiles.ExplosionTile;

import java.util.Timer;
import java.util.TimerTask;

public abstract class Booster extends BreakableTile {
    @Override
    public void HandleCollision(Entity collided) {
        if(collided instanceof ExplosionTile && !isInvincible){
            DestroySelf();
        }
        else if(collided instanceof Bomberman){
            Boost((Bomberman) collided);
            DestroySelf();
        }
    }

    protected abstract void Boost(Bomberman bomberman);

    public Booster(){
        super.isInvincible = true;
    }

    public void RemoveInvincibility(){
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                isInvincible = false;
            }
        }, 1500L);
    }

    @Override
    public boolean isSolid(){
        return false;
    }
}
