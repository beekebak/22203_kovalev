package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Tiles.Boosters.ExplosionTile;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Levelio.LevelReader;
import javafx.application.Platform;
import javafx.beans.Observable;
import javafx.concurrent.Task;
import javafx.scene.image.Image;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

import static com.lab_2_java.Utility.CoordinatesConverter.*;
import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Tiles.Tile;
public class GameLevel {
    private static final Executor explosionTimer = Executors.newSingleThreadExecutor();
    private final Image backGround = new Image("/sprites/background.png");
    private Bomberman bomberman = new Bomberman(150,150);
    private List<List<Tile>> gameGrid;

    public GameLevel(){
        InitializeGameGrid();
        SolidCollisionChecker.setLevel(this);
    }

    public void InitializeGameGrid(){
        LevelReader levelReader = new LevelReader("src/main/resources/levels/campaign_levels/level1-1.json");
        gameGrid = levelReader.InitializeGrid();
    }

    public Image getCellImage(int viewX, int viewY){
        if(gameGrid.get(viewY).get(viewX) == null){
            return null;
        }
        return gameGrid.get(viewY).get(viewX).getSprite();
    }

    public Observable getCellObservable(int viewX, int viewY){
        return gameGrid.get(viewY).get(viewX).isBrokenProperty();
    }

    Tile getCellContainmentFromView(int x, int y){
        if(gameGrid.get(ConvertViewCoordinateToGridCoordinate(y)).
                get(ConvertViewCoordinateToGridCoordinate(x)) == null){
            return null;
        }
        return gameGrid.get(ConvertViewCoordinateToGridCoordinate(y)).
                get(ConvertViewCoordinateToGridCoordinate(x));
    }

    public int GetGridColumnsCount(){
        return gameGrid.getFirst().size();
    }

    public int GetGridRowsCount(){
        return gameGrid.size();
    }

    public int GetXSceneSize(){
        return ConvertGridCoordinateToViewCoordinate(gameGrid.getFirst().size());
    }
    public int GetYSceneSize(){
        return ConvertGridCoordinateToViewCoordinate(gameGrid.size());
    }
    
    public Image getBackGround() {
        return backGround;
    }
    public Bomberman getBomberman(){
        return bomberman;
    }

    public int GetLastBombXCoordinate(){
        return ConvertViewCoordinateToGridCoordinate(bomberman.getYValue()+bomberman.getYSize());
    }

    public int GetLastBombYCoordinate(){
        return ConvertViewCoordinateToGridCoordinate(bomberman.getXValue()+bomberman.getXSize());
    }

    public void ContinueExplosion(List<int[]> explosions, int row, int col, int drow, int dcol, int step, int maxStep){
        if(step == maxStep) return;
        Tile tileOnExplosionWay = gameGrid.get(row+drow).get(col+dcol);
        if(tileOnExplosionWay == null){
            gameGrid.get(row+drow).set(col+dcol, new ExplosionTile());
            explosions.add(new int[]{row+drow, col+dcol});
            ContinueExplosion(explosions, row+drow, col+dcol, drow, dcol, step+1, maxStep);
        }
        else if(tileOnExplosionWay instanceof BreakableTile){
            gameGrid.get(row+drow).set(col+dcol, null);
        }
    }

    private void CleanExplosions(List<int[]> explosions){
        for(var explosion : explosions){
            gameGrid.get(explosion[0]).set(explosion[1], null);
        }
    }

    private void StartExplosion(int row, int col){
        List<int[]> explosions = new ArrayList<>();
        gameGrid.get(row).set(col, new ExplosionTile());
        explosions.add(new int[]{row, col});
        int power = bomberman.getBombPower();
        ContinueExplosion(explosions, row, col, 1, 0, 0, power);
        ContinueExplosion(explosions, row, col, -1, 0, 0, power);
        ContinueExplosion(explosions, row, col, 0, -1, 0, power);
        ContinueExplosion(explosions, row, col, 0, 1, 0, power);
        Task<Void> awaitExplosionsEnd = new Task<Void>() {
            @Override
            public Void call() throws Exception {
                try{
                    Thread.sleep(1000);
                    Platform.runLater(() -> {CleanExplosions(explosions);});
                }
                catch (InterruptedException e) {}
                return null;
            }
        };
        explosionTimer.execute(awaitExplosionsEnd);
    }

    public boolean BombEvent(){
        Tile bomb = bomberman.PlantBomb();
        if(bomb == null) return false;
        int col = ConvertViewCoordinateToGridCoordinate(bomberman.getXValue()+bomberman.getXSize());
        int row = ConvertViewCoordinateToGridCoordinate(bomberman.getYValue()+bomberman.getYSize());
        gameGrid.get(row).set(col, bomb);
        bomb.isBrokenProperty().addListener(observable -> {StartExplosion(row, col);});
        return true;
    }
}
