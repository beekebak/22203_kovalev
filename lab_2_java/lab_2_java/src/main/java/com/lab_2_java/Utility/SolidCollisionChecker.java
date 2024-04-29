package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.Tiles.Boosters.ExplosionTile;
import com.lab_2_java.Entities.Tiles.Tile;

import java.util.*;

public class SolidCollisionChecker {
    private static GameLevel gameLevel;

    static void setLevel(GameLevel level){
        gameLevel = level;
    }

    public static boolean CheckMoveValidity(Creature creature, int dx, int dy){
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

    public static Set<Tile> FindCollidedCells(Creature creature){
        int leftX = creature.getXValue()+creature.getCenterXShift()-creature.getXSize();
        int rightX = creature.getXValue()+creature.getCenterXShift()+creature.getXSize();
        int upperY = creature.getYValue()+creature.getCenterYShift()-creature.getYSize();
        int lowerY = creature.getYValue()+creature.getCenterYShift()+creature.getYSize();
        int Xcoords[] = {leftX, rightX};
        int Ycoords[] = {upperY, lowerY};
        Set<Tile> usedCells = new HashSet<>();
        for(int i = 0; i < Xcoords.length; i++){
            for(int j = 0; j < Ycoords.length; j++){
                usedCells.add(gameLevel.getCellContainmentFromView(Xcoords[i], Ycoords[j]));
            }
        }
        return usedCells;
    }
}
