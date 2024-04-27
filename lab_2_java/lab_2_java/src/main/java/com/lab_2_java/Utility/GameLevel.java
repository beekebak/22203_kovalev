package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Entities.Tiles.Tile;
import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableArray;
import javafx.collections.ObservableList;
import javafx.scene.image.Image;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import static javafx.collections.FXCollections.observableArrayList;

public class GameLevel {
    private int gridXSize = 10;
    private int gridYSize = 10;

    public int getGridXSize() {
        return gridXSize;
    }

    public int getGridYSize() {
        return gridYSize;
    }

    private static class TileWrapper<T extends Tile>{
        int gridXCoordinate;
        int gridYCoordinate;
        T gameObject;
        TileWrapper(int gridXCoordinate, int gridYCoordinate, T gameObject){
            this.gameObject = gameObject;
            this.gridYCoordinate = gridYCoordinate;
            this.gridXCoordinate = gridXCoordinate;
        }
    }
    private Image backGround = new Image("/sprites/background.png");
    private Bomberman bomberman = new Bomberman();
    private List<List<TileWrapper<Tile>>> gameGrid;
    private ObservableList<TileWrapper<Tile>> destroyableBoxes = FXCollections.observableArrayList(
            breakableTile -> new Observable[] {breakableTile.gameObject.isBrokenProperty()});

    public GameLevel(){
        InitializeGameGrid();
        SolidCollisionChecker.setLevel(this);
    }

    public void InitializeGameGrid(){
        gameGrid = new ArrayList<>();
        for(int i = 0; i < gridXSize; i++) gameGrid.add(new ArrayList<>(Collections.nCopies(gridYSize, null)));
        gameGrid.get(0).set(0, new TileWrapper<>(0, 0, new BreakableTile()));
        gameGrid.get(2).set(2, new TileWrapper<>(2, 2, new BreakableTile()));
        gameGrid.get(0).set(2, new TileWrapper<>(0, 2, new BreakableTile()));
        gameGrid.get(2).set(0, new TileWrapper<>(2, 0, new BreakableTile()));
        gameGrid.get(0).set(1, new TileWrapper<>(0, 1, new BreakableTile()));
        gameGrid.get(1).set(2, new TileWrapper<>(1, 2, new BreakableTile()));
    }

    public Image getCellImage(int viewX, int viewY){
        if(gameGrid.get(viewX).get(viewY) == null){
            return null;
        }
        return gameGrid.get(viewX).get(viewY).gameObject.getSprite();
    }

    public Observable getCellObservable(int viewX, int viewY){
        return gameGrid.get(viewX).get(viewY).gameObject.isBrokenProperty();
    }

    Tile getCellContainmentFromView(int x, int y){
        if(gameGrid.get(ConvertViewCoordinateToGridCoordinate(x)).
                get(ConvertViewCoordinateToGridCoordinate(y)) == null){
            return null;
        }
        return gameGrid.get(ConvertViewCoordinateToGridCoordinate(x)).
                get(ConvertViewCoordinateToGridCoordinate(y)).gameObject;
    }
    
    public Image getBackGround() {
        return backGround;
    }
    public Bomberman getBomberman(){
        return bomberman;
    }

    public int ConvertGridCoordinateToViewCoordinate(int coordinate){
        return coordinate*48;
    }
    public int CenterViewCoordinate(int coordinate){
        return coordinate/48*48+24;
    }
    public int ConvertViewCoordinateToGridCoordinate(int coordinate){
        return coordinate/48;
    }
}
