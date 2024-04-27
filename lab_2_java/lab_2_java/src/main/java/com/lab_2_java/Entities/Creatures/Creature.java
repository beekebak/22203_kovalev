package com.lab_2_java.Entities.Creatures;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Utility.SolidCollisionChecker;
import javafx.beans.property.*;

public abstract class Creature implements Entity {
    protected int speed;
    protected int xSize;
    protected int ySize;
    protected int centerXShift;
    protected int centerYShift;

    public int getCenterXShift() {
        return centerXShift;
    }

    public int getCenterYShift() {
        return centerYShift;
    }

    public int getXSize() {
        return xSize;
    }

    public int getYSize() {
        return ySize;
    }
    protected SimpleIntegerProperty x = new SimpleIntegerProperty();
    protected BooleanProperty isAlive = new SimpleBooleanProperty(true);

    protected SimpleIntegerProperty y = new SimpleIntegerProperty();

    public SimpleIntegerProperty getX() {
        return x;
    }

    public int getXValue() {
        return x.get();
    }

    public void setX(int x) {
        this.x.set(x);
    }

    public SimpleIntegerProperty getY() {
        return y;
    }

    public int getYValue() {
        return y.get();
    }

    public void setY(int y) {
        this.y.set(y);
    }
    public int getSpeed() {
        return speed;
    }

    final protected SolidCollisionChecker collisionChecker;

    protected Creature(int speed, SolidCollisionChecker collisionChecker) {
        this.speed = speed;
        this.collisionChecker = collisionChecker;
    }

    protected Creature(int speed, SolidCollisionChecker collisionChecker, int x, int y) {
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
