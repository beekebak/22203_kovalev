package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.Boosters.ExplosionTile;
import com.lab_2_java.Utility.SolidCollisionChecker;

public abstract class Enemy extends Creature {
    protected Enemy(int speed, SolidCollisionChecker collisionChecker) {
        super(speed, collisionChecker);
    }
    public void HandleCollision(Entity collided){
        if(collided instanceof ExplosionTile){
            DestroySelf();
        }
    }
}
