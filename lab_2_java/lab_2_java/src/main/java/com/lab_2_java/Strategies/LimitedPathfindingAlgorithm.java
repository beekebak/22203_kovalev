package com.lab_2_java.Strategies;

import com.lab_2_java.Algorithms.PathfindingAlgorithm;
import com.lab_2_java.Entities.Creatures.Enemies.Enemy;
import com.lab_2_java.Algorithms.PathInfo;
import com.lab_2_java.CollisionHandlers.SolidityType;

public class LimitedPathfindingAlgorithm extends MovementAlgorithm {
    private ProxyPathfindingAlgorithm pathfindingStrategyImplementation;
    private ProxySimpleAlgorithm defaultStrategyImplementation;
    private int visionLength;
    private boolean pathfindingAlgorithmStillMoves = false;
    private boolean simpleAlgorithmStillMoves = false;

    public LimitedPathfindingAlgorithm(int pathfindingAlgorithmLength, int visionLength){
        pathfindingStrategyImplementation = new ProxyPathfindingAlgorithm(pathfindingAlgorithmLength);
        defaultStrategyImplementation = new ProxySimpleAlgorithm(pathfindingAlgorithmLength);
        this.visionLength = visionLength;
    }
    @Override
    public void MoveImplementation(Enemy creature, SolidityType type){
        if(pathfindingAlgorithmStillMoves){
            pathfindingStrategyImplementation.MoveImplementation(creature, type);
            pathfindingAlgorithmStillMoves = !pathfindingStrategyImplementation.Done();
            return;
        }
        else if(simpleAlgorithmStillMoves){
            defaultStrategyImplementation.MoveImplementation(creature, type);
            simpleAlgorithmStillMoves = !defaultStrategyImplementation.Done();
            return;
        }
        PathInfo info = PathfindingAlgorithm.GetRangeToBomberman(creature, type);
        if(info.size < visionLength){
            pathfindingAlgorithmStillMoves = true;
        }
        else{
            simpleAlgorithmStillMoves = true;
        }
    }
}
