package com.lab_2_java.CollisionHandlers;

import com.lab_2_java.Entities.Creatures.Creature;
import javafx.scene.shape.Rectangle;

public class MovingCollisionChecker{
    public static boolean CheckCollision(Creature first, Creature second){
        int firstY = first.getYValue() + first.getCenterYShift();
        int firstX = first.getXValue() + first.getCenterXShift();
        int secondY = second.getYValue() + second.getCenterYShift();
        int secondX = second.getXValue() + second.getCenterXShift();
        Rectangle firstRect = new Rectangle(firstX, firstY, first.getXSize(), first.getYSize());
        Rectangle secondRect = new Rectangle(secondX, secondY, second.getXSize(), second.getYSize());
        return firstRect.intersects(secondRect.getBoundsInLocal());
    }
}
