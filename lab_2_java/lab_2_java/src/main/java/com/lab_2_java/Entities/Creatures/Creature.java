package com.lab_2_java.Entities.Creatures;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Utility.CollisionChecker;
import javafx.beans.property.*;

public abstract class Creature implements Entity {
    private int speed;
    private SimpleIntegerProperty x = new SimpleIntegerProperty();
    protected BooleanProperty isAlive = new SimpleBooleanProperty(true);

    private  SimpleIntegerProperty y = new SimpleIntegerProperty();

    public SimpleIntegerProperty getX() {
        return x;
    }

    public void setX(int x) {
        this.x.set(x);
    }

    public SimpleIntegerProperty getY() {
        return y;
    }

    public void setY(int y) {
        this.y.set(y);
    }
    public int getSpeed() {
        return speed;
    }

    final private CollisionChecker collisionChecker;

    protected Creature(int speed, CollisionChecker collisionChecker) {
        this.speed = speed;
        this.collisionChecker = collisionChecker;
    }

    protected Creature(int speed, CollisionChecker collisionChecker, int x, int y) {
        this.speed = speed;
        this.collisionChecker = collisionChecker;
        setX(x);
        setY(y);
    }

    public abstract void Move();

    protected void DestroySelf() {
        isAlive.set(false);
    }
}
