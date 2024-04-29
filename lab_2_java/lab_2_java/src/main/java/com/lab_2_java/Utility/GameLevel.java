package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.Tiles.BombTile;
import com.lab_2_java.Entities.Tiles.Boosters.ExplosionTile;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Levelio.LevelReader;
import javafx.animation.AnimationTimer;
import javafx.application.Platform;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.concurrent.Task;
import javafx.scene.image.Image;

import java.util.*;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

import static com.lab_2_java.Utility.CoordinatesConverter.*;
import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Tiles.Tile;
public class GameLevel {
    private static final Executor explosionTimer = Executors.newSingleThreadExecutor();
    private final Image backGround = new Image("/sprites/background.png");
    private Bomberman bomberman;
    private List<Creature> enemies;
    private List<List<TileWrapper>> gameGrid;
    private int frameRateCounter = 0;

    public List<Creature> getEnemies() {
        return enemies;
    }

    public GameLevel(){
        InitializeGame();
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
    }

    private void UpdateLevel(){
        frameRateCounter++;
        Set<Tile> collidedTiles = SolidCollisionChecker.FindCollidedCells(bomberman);
        for(var tile:collidedTiles){
            HandleCreatureCollisionWithTile(bomberman, tile);
        }
        if(frameRateCounter % 8 == 0) {
            for (var enemy : enemies) {
                enemy.Move();
                HandleCreatureCollisionsWithCreature(bomberman, enemy);
                collidedTiles = SolidCollisionChecker.FindCollidedCells(enemy);
                for(var tile:collidedTiles){
                    HandleCreatureCollisionWithTile(enemy, tile);
                }
            }
        }
        if(frameRateCounter % 8 == 0) frameRateCounter = 0;
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
            gameGrid.get(i).get(j).setTile(null);
        });
    }

    public void InitializeGame(){
        LevelReader levelReader = new LevelReader("src/main/resources/levels/campaign_levels/level1-1.json");
        gameGrid = levelReader.InitializeGrid();
        bomberman = (Bomberman) levelReader.InitializePlayer();
        enemies = levelReader.InitializeEnemies();
        AnimationTimer frameUpdater = new AnimationTimer() {
            @Override
            public void handle(long now) {
                UpdateLevel();
            }
        };
        frameUpdater.start();
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
            gameGrid.get(row+drow).get(col+dcol).setTile(null);
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

    public void BombEvent(){
        BombTile bomb = bomberman.PlantBomb();
        if(bomb == null) return;
        int col = ConvertViewCoordinateToGridCoordinate(bomberman.getXValue()+bomberman.getXSize());
        int row = ConvertViewCoordinateToGridCoordinate(bomberman.getYValue()+bomberman.getYSize());
        gameGrid.get(row).get(col).setTile(bomb);
        RegisterBreakableTile(bomb, row, col);
        AnimationTimer bombSolidation = new AnimationTimer() {
            @Override
            public void handle(long now) {
                if(!SolidCollisionChecker.FindCollidedCells(bomberman).contains(bomb)){
                    bomb.MakeSolid();
                    this.stop();
                }
            }
        };
        bombSolidation.start();
        bomb.isBrokenProperty().addListener(observable -> {bombSolidation.stop();});
        bomb.isBrokenProperty().addListener(observable -> {StartExplosion(row, col);});
    }
}
