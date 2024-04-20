package Entities.Creatures.Enemies;

import Entities.Creatures.Creature;
import Entities.Entity;
import Entities.Objects.Tiles.Explosion;
import Entities.Objects.Tiles.Tile;

public abstract class Enemy extends Creature {

    public Enemy(boolean alive, int speed_) {
        super(alive, speed_);
    }

    protected abstract void ChooseMoveDirection();

    protected void DestroySelf(){

    }
    public void HandleCollisionEvent(Entity collidedObject) {
        if(collidedObject instanceof Explosion){
            DestroySelf();
        }
        else if(collidedObject instanceof Tile && ((Tile) collidedObject).isSolidObject()){
            ChooseMoveDirection();
        }
    }
}
