package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.Tile;

public class SolidCollisionChecker {
    private static GameLevel gameLevel;

    static void setLevel(GameLevel level){
        gameLevel = level;
    }

    public boolean CheckMoveValidity(Creature creature, int dx, int dy){
        int leftX = creature.getXValue()+creature.getCenterXShift()+dx-creature.getXSize();
        int rightX = creature.getXValue()+creature.getCenterXShift()+dx+creature.getXSize();
        int upperY = creature.getYValue()+creature.getCenterYShift()+dy-creature.getYSize();
        int lowerY = creature.getYValue()+creature.getCenterYShift()+dy+creature.getYSize();

        Entity containmentOfRequestedCell = gameLevel.getCellContainmentFromView(leftX, upperY);
            if(containmentOfRequestedCell instanceof Tile && ((Tile) containmentOfRequestedCell).isSolid()) {
            return false;
        }
        containmentOfRequestedCell = gameLevel.getCellContainmentFromView(rightX, upperY);
        if(containmentOfRequestedCell instanceof Tile && ((Tile) containmentOfRequestedCell).isSolid()) {
            return false;
        }
        containmentOfRequestedCell = gameLevel.getCellContainmentFromView(leftX, lowerY);
        if(containmentOfRequestedCell instanceof Tile && ((Tile) containmentOfRequestedCell).isSolid()) {
            return false;
        }
        containmentOfRequestedCell = gameLevel.getCellContainmentFromView(rightX, lowerY);
        if(containmentOfRequestedCell instanceof Tile && ((Tile) containmentOfRequestedCell).isSolid()) {
            return false;
        }
        return true;
    }
}
