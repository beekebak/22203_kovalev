package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Creature;
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
        int Xcoords[] = {leftX, rightX};
        int Ycoords[] = {upperY, lowerY};
        for(int i = 0; i < Xcoords.length; i++){
            for(int j = 0; j < Ycoords.length; j++){
                Tile containmentOfRequestedCell = gameLevel.getCellContainmentFromView(Xcoords[i], Ycoords[j]);
                if(containmentOfRequestedCell != null && (containmentOfRequestedCell).isSolid()) {
                    return false;
                }
            }
        }
        return true;
    }
}
