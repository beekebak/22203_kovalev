package com.lab_2_java.Entities.Tiles.Boosters;

import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Entities.Tiles.ExplosionTile;

public abstract class Booster extends BreakableTile {
    @Override
    public void HandleCollision(Entity collided) {
        if(collided instanceof ExplosionTile){
            DestroySelf();
        }
        else if(collided instanceof Bomberman){
            Boost((Bomberman) collided);
        }
    }

    protected abstract void Boost(Bomberman bomberman);
}
