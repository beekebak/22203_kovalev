package Entities.Creatures;

import Entities.Entity;

public abstract class Creature implements Entity {
    private boolean isAlive;
    private int speed;
    public Creature(boolean alive, int speed_){
        isAlive = alive;
        speed = speed_;
    }
    public boolean isAlive() {

        return isAlive;
    }
    public void setAlive(boolean alive) {

        isAlive = alive;
    }
    public int getSpeed() {
        return speed;
    }
    protected void DestroySelf() throws NoSuchMethodException {
        throw new NoSuchMethodException(); // this method should not ever be invoked if not overriden
    }
}
