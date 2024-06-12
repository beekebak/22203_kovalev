package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.Tiles.BombTile;
import com.lab_2_java.Entities.Tiles.Tile;
import com.lab_2_java.Models.GameLevel;

public class BombLookingAlgorithm {
    private static GameLevel level;

    public static void setLevel(GameLevel gameLevel){
        level = gameLevel;
    }

    private static boolean DFS(int startX, int startY, int dx, int dy, int maxX, int maxY, int depth, int maxDepth){
        if(depth > maxDepth) return false;
        if(startX + dx < 0 || startX + dx > maxX || startY + dy < 0 || startY+dy > maxY) return false;
        Tile tile = level.getCellContainment(startY, startX);
        if(tile instanceof BombTile) return true;
        return DFS(startX+dx, startY+dy, dx, dy, maxX, maxY, depth+1, maxDepth);
    }

    public static MoveDirections CheckBombs(Creature creature, int depth){
        int startY = CoordinatesConverter.ConvertViewCoordinateToGridCoordinate(creature.getYValue()+
                creature.getCenterYShift());
        int startX = CoordinatesConverter.ConvertViewCoordinateToGridCoordinate(creature.getXValue()+
                creature.getCenterXShift());
        if(DFS(startX, startY, 1, 0, level.GetGridColumnsCount(), level.GetGridRowsCount(), 0, depth)){
            return MoveDirections.LEFT;
        }
        if(DFS(startX, startY, -1, 0, level.GetGridColumnsCount(), level.GetGridRowsCount(), 0, depth)){
            return MoveDirections.RIGHT;
        }
        if(DFS(startX, startY, 0, -1, level.GetGridColumnsCount(), level.GetGridRowsCount(), 0, depth)){
            return MoveDirections.DOWN;
        }
        if(DFS(startX, startY, 0, 1, level.GetGridColumnsCount(), level.GetGridRowsCount(), 0, depth)){
            return MoveDirections.UP;
        }
        return MoveDirections.NONE;
    }
}
