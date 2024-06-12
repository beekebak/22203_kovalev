package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.ExplosionTile;
import com.lab_2_java.Utility.MoveDirections;

public abstract class Enemy extends Creature {
    protected Enemy(int speed) {
        super(speed);
    }

    public Enemy(int speed, int xCoord, int yCoord) {
        super(speed, xCoord, yCoord);
    }

    public void HandleCollision(Entity collided){
        if(collided instanceof ExplosionTile){
            DestroySelf();
        }
    }
}
