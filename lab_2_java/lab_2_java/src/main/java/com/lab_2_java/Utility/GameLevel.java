package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.Tiles.BombTile;
import com.lab_2_java.Entities.Tiles.Boosters.Booster;
import com.lab_2_java.Entities.Tiles.ExplosionTile;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Levelio.LevelReader;
import javafx.application.Platform;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.scene.image.Image;

import java.util.*;

import static com.lab_2_java.Utility.CoordinatesConverter.*;
import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Tiles.Tile;

public class GameLevel {
    private final Image backGround = new Image("/sprites/background.png");
    private Bomberman bomberman;
    private List<Creature> enemies;
    private List<List<TileWrapper>> gameGrid;
    private int frameRateCounter = 0;

    public List<Creature> getEnemies() {
        return enemies;
    }

    public GameLevel(String path){
        InitializeGame(path);
        SolidCollisionChecker.setLevel(this);
        bomberman.GetProperty().addListener(observable -> {
            System.out.println("DEAD");
        });
    }

    private void HandleCreatureCollisionsWithCreature(Creature collider, Creature collided){
        if(MovingCollisionChecker.CheckCollision(collided, collider)){
            collided.HandleCollision(collider);
            collider.HandleCollision(collided);
        }
    }

    private void HandleCreatureCollisionWithTile(Creature creature, Tile tile){
        creature.HandleCollision(tile);
        if(tile != null) tile.HandleCollision(creature);
    }

    public void UpdateLevel(){
        frameRateCounter++;
        Set<Tile> collidedTiles = SolidCollisionChecker.FindCollidedCells(bomberman);
        for(var tile:collidedTiles){
            HandleCreatureCollisionWithTile(bomberman, tile);
        }
        if(frameRateCounter % 6 == 0) {
            for (var enemy : enemies) {
                enemy.Move();
                HandleCreatureCollisionsWithCreature(bomberman, enemy);
                collidedTiles = SolidCollisionChecker.FindCollidedCells(enemy);
                for(var tile:collidedTiles){
                    HandleCreatureCollisionWithTile(enemy, tile);
                }
            }
        }
        if(frameRateCounter % 6 == 0) frameRateCounter = 0;
    }

    public static class TileWrapper{
        private Tile tile;
        public SimpleBooleanProperty IsPresent() {
            return isNull;
        }

        private final SimpleBooleanProperty isNull;

        public TileWrapper(Tile tile) {
            this.tile = tile;
            isNull = new SimpleBooleanProperty(false);
            if(tile == null) isNull.set(true);
        }

        public Tile getTile() {
            return tile;
        }
        public SimpleBooleanProperty IsNull() {
            return isNull;
        }
        public void setTile(Tile tile) {
            this.tile = tile;
            if(tile == null) isNull.set(true);
            else isNull.set(false);
        }
    }

    private void RegisterBreakableTile(BreakableTile tile, int i, int j){
        tile.isBrokenProperty().addListener(observable -> {
            if(tile.getUnderlyingTile() != null) {
                gameGrid.get(i).get(j).setTile(null);
                gameGrid.get(i).get(j).setTile(tile.getUnderlyingTile());
                RegisterBreakableTile(tile.getUnderlyingTile(), i, j);
                if(tile.getUnderlyingTile() instanceof Booster) {
                    ((Booster) tile.getUnderlyingTile()).RemoveInvincibility();
                }
            }
            else gameGrid.get(i).get(j).setTile(tile.getUnderlyingTile());
        });
    }

    public void InitializeGame(String path){
        LevelReader levelReader = new LevelReader(path);
        gameGrid = levelReader.InitializeGrid();
        for(int i = 0; i < gameGrid.size(); i++){
            for(int j = 0; j < gameGrid.getFirst().size(); j++){
                if(gameGrid.get(i).get(j).getTile() instanceof BreakableTile){
                    RegisterBreakableTile((BreakableTile) gameGrid.get(i).get(j).getTile(), i, j);
                }
            }
        }
        bomberman = (Bomberman) levelReader.InitializePlayer();
        enemies = levelReader.InitializeEnemies();
    }

    public Image getCellImage(int viewX, int viewY){
        if(gameGrid.get(viewY).get(viewX).getTile() == null){
            return null;
        }
        return gameGrid.get(viewY).get(viewX).getTile().getSprite();
    }

    public SimpleBooleanProperty getCellContainmentProperty(int X, int Y){
        return gameGrid.get(Y).get(X).IsPresent();
    }

    public Tile getCellContainmentFromView(int x, int y){
        if(gameGrid.get(ConvertViewCoordinateToGridCoordinate(y)).
                get(ConvertViewCoordinateToGridCoordinate(x)).getTile() == null){
            return null;
        }
        return gameGrid.get(ConvertViewCoordinateToGridCoordinate(y)).
                get(ConvertViewCoordinateToGridCoordinate(x)).getTile();
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

    public void ContinueExplosion(List<int[]> explosions, int row, int col, int drow, int dcol, int step, int maxStep){
        if(step == maxStep) return;
        Tile tileOnExplosionWay = gameGrid.get(row+drow).get(col+dcol).getTile();
        if(tileOnExplosionWay == null){
            gameGrid.get(row+drow).get(col+dcol).setTile(new ExplosionTile());
            explosions.add(new int[]{row+drow, col+dcol});
            ContinueExplosion(explosions, row+drow, col+dcol, drow, dcol, step+1, maxStep);
        }
        else if(tileOnExplosionWay instanceof BreakableTile){
            gameGrid.get(row+drow).get(col+dcol).getTile().HandleCollision(new ExplosionTile());
        }
    }

    private void CleanExplosions(List<int[]> explosions){
        for(var explosion : explosions){
            gameGrid.get(explosion[0]).get(explosion[1]).setTile(null);
        }
    }

    private void StartExplosion(int row, int col){
        List<int[]> explosions = new ArrayList<>();
        gameGrid.get(row).get(col).setTile(new ExplosionTile());
        explosions.add(new int[]{row, col});
        int power = bomberman.getBombPower();
        ContinueExplosion(explosions, row, col, 1, 0, 0, power);
        ContinueExplosion(explosions, row, col, -1, 0, 0, power);
        ContinueExplosion(explosions, row, col, 0, -1, 0, power);
        ContinueExplosion(explosions, row, col, 0, 1, 0, power);
        Timer explosionTimer = new Timer();
        TimerTask awaitExplosionsEnd = new TimerTask() {
            @Override
            public void run(){
                Platform.runLater(() -> {CleanExplosions(explosions);});
            }
        };
        explosionTimer.schedule(awaitExplosionsEnd, 1000L);
    }

    public void BombEvent(){
        BombTile bomb = bomberman.PlantBomb();
        if(bomb == null) return;
        int col = ConvertViewCoordinateToGridCoordinate(bomberman.getXValue()+bomberman.getXSize());
        int row = ConvertViewCoordinateToGridCoordinate(bomberman.getYValue()+bomberman.getYSize());
        gameGrid.get(row).get(col).setTile(bomb);
        RegisterBreakableTile(bomb, row, col);
        Timer timer = new Timer();
        TimerTask bombSolidationTask = new TimerTask() {
            @Override
            public void run(){
                if(!SolidCollisionChecker.FindCollidedCells(bomberman).contains(bomb)){
                    bomb.MakeSolid();
                    System.out.println("SOLID");
                    this.cancel();
                }
            }
        };
        timer.schedule(bombSolidationTask, 0L, 50L);
        bomb.isBrokenProperty().addListener(observable -> {timer.cancel();});
        bomb.isBrokenProperty().addListener(observable -> {StartExplosion(row, col);});
    }
}
