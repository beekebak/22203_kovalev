package com.lab_2_java.Algorithms;

import com.lab_2_java.CollisionHandlers.SolidityType;
import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Models.GameLevel;
import com.lab_2_java.Utility.MoveDirections;

import java.util.Iterator;
import java.util.PriorityQueue;

import static java.lang.Math.*;

public class PathfindingAlgorithm {
    private static GameLevel level;
    public static void setLevel(GameLevel gameLevel){
        level = gameLevel;
    }

    public static PathInfo GetRangeToBomberman(Creature from, SolidityType type){
        return level.GetRange(from, type);
    }

    private static class PathfindingTileWrapper implements Comparable<PathfindingTileWrapper>{
        private int x;
        private int y;
        private int range;

        private int rangeToTarget;

        private MoveDirections direction;

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public MoveDirections getDirection() {
            return direction;
        }

        public int getRange() {
            return range;
        }

        public int getRangeToTarget() {
            return rangeToTarget;
        }

        public void setRange(int range) {
            this.range = range;
        }

        public void setDirection(MoveDirections direction){
            this.direction = direction;
        }

        PathfindingTileWrapper(int x, int y, int range, int rangeToTarget, MoveDirections direction){
            this.x = x;
            this.y = y;
            this.range = range;
            this.rangeToTarget = rangeToTarget;
            this.direction = direction;
        }

        @Override
        public int compareTo(PathfindingTileWrapper o){
            return Integer.compare(rangeToTarget, o.getRangeToTarget());
        }
    }

    private static int GetManhattanLength(int startX, int startY, int endX, int endY){
        return abs(startY-endY) + abs(startX-endX);
    }

    private static void AddIfPossible(int x, int y, int sizeX, int sizeY, int endX, int endY, int prevLength,
                                      boolean[][] usedGrid, PriorityQueue<PathfindingTileWrapper> candidates,
                                      SolidityType maxPerception, MoveDirections direction){
        if(x < 0 || x >= sizeX) return;
        if(y < 0 || y >= sizeY) return;
        if(maxPerception.ordinal() < level.getSolidityType(x, y).ordinal()) return;
        if(usedGrid[x][y]){
            Iterator<PathfindingTileWrapper> iter = candidates.iterator();
            while(iter.hasNext()){
                PathfindingTileWrapper wrapper = iter.next();
                if(wrapper.getY() == y && wrapper.getX() == x){
                    iter.remove();
                    if(wrapper.getRange() > GetManhattanLength(x, y, endX, endY) + prevLength + 1){
                        wrapper.setRange(GetManhattanLength(x, y, endX, endY) + prevLength + 1);
                        wrapper.setDirection(direction);
                    }
                    candidates.add(wrapper);
                    break;
                }
            }
            return;
        }
        candidates.add(new PathfindingTileWrapper(x, y, GetManhattanLength(x, y, endX, endY) + prevLength + 1,
                GetManhattanLength(x, y, endX, endY), direction));
        usedGrid[x][y] = true;
    }

    public static PathInfo AlgorithmImplementation(int startX, int startY, int endX, int endY, int sizeX, int sizeY,
                                                   SolidityType maxPerception){
        if(startX == endX && startY == endY) return new PathInfo(0, MoveDirections.NONE);
        boolean[][] usedGrid = new boolean[sizeX][sizeY];
        usedGrid[startX][startY] = true;
        PriorityQueue<PathfindingTileWrapper> candidateCells = new PriorityQueue<>();
        AddIfPossible(startX+1, startY, sizeX, sizeY, endX, endY, 0, usedGrid, candidateCells,
                maxPerception, MoveDirections.DOWN);
        AddIfPossible(startX-1, startY, sizeX, sizeY, endX, endY, 0, usedGrid, candidateCells,
                maxPerception, MoveDirections.UP);
        AddIfPossible(startX, startY+1, sizeX, sizeY, endX, endY, 0, usedGrid, candidateCells,
                maxPerception, MoveDirections.RIGHT);
        AddIfPossible(startX, startY-1, sizeX, sizeY, endX, endY, 0, usedGrid, candidateCells,
                maxPerception, MoveDirections.LEFT);
        while(!candidateCells.isEmpty()){
            PathfindingTileWrapper tile = candidateCells.poll();
            if(tile.getX() == endX && tile.getY() == endY) return new PathInfo(tile.getRange(), tile.getDirection());
            AddIfPossible(tile.getX()+1, tile.getY(), sizeX, sizeY, endX, endY,
                    tile.range - GetManhattanLength(tile.getX(), tile.getY(), endX, endY),
                    usedGrid, candidateCells, maxPerception, tile.getDirection());
            AddIfPossible(tile.getX()-1, tile.getY(), sizeX, sizeY, endX, endY,
                    tile.range - GetManhattanLength(tile.getX(), tile.getY(), endX, endY),
                    usedGrid, candidateCells, maxPerception, tile.getDirection());
            AddIfPossible(tile.getX(), tile.getY()+1, sizeX, sizeY, endX, endY,
                    tile.range - GetManhattanLength(tile.getX(), tile.getY(), endX, endY),
                    usedGrid, candidateCells, maxPerception, tile.getDirection());
            AddIfPossible(tile.getX(), tile.getY()-1, sizeX, sizeY, endX, endY,
                    tile.range - GetManhattanLength(tile.getX(), tile.getY(), endX, endY),
                    usedGrid, candidateCells, maxPerception, tile.getDirection());
        }
        return new PathInfo(0, MoveDirections.NONE);
    }
}
