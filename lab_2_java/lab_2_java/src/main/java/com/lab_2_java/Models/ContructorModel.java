package com.lab_2_java.Models;

import com.lab_2_java.Levelio.LevelWriter;
import com.lab_2_java.Utility.ConstructorTileWrapper;
import com.lab_2_java.Utility.ObservableConstructorTileWrapper;
import com.lab_2_java.Utility.TriCallback;
import javafx.scene.image.Image;

import java.util.*;

public class ContructorModel {
    private final LevelWriter writer = new LevelWriter();
    private ConstructorTileWrapper currentTile;
    private List<List<ObservableConstructorTileWrapper>> grid;
    private Map<String, ConstructorTileWrapper> tilesPool;
    private TriCallback<Void, Integer, Integer, List<List<ObservableConstructorTileWrapper>>> RegisterCallback;

    public ConstructorTileWrapper getCurrentTile() {
        return currentTile;
    }

    public void setCurrentTile(ConstructorTileWrapper currentTile) {
        this.currentTile = currentTile;
    }


    public Map<String, ConstructorTileWrapper> getTilesPool() {
        return tilesPool;
    }

    public ContructorModel(TriCallback<Void, Integer, Integer, List<List<ObservableConstructorTileWrapper>>> Register){
        RegisterCallback = Register;
        InitializeTilesPool();
    }

    private void InitializeTilesPool(){
        tilesPool = new HashMap<>();
        tilesPool.putIfAbsent("Metal", new ConstructorTileWrapper("Metal", "Tile",
                new Image("/sprites/MetalBox.png")));
        tilesPool.putIfAbsent("Wooden", new ConstructorTileWrapper("Wooden", "Tile",
                new Image("/sprites/box.png")));
        tilesPool.putIfAbsent("BombCountBooster", new ConstructorTileWrapper("Wooden",
                "Tile", new Image("/sprites/BombCountBooster.png"), "BombCountBooster"));
        tilesPool.putIfAbsent("BombPowerBooster", new ConstructorTileWrapper("Wooden",
                "Tile", new Image("/sprites/BombPowerBooster.png"), "BombPowerBooster"));
        tilesPool.putIfAbsent("SpeedBooster", new ConstructorTileWrapper("Wooden",
                "Tile", new Image("/sprites/SpeedBooster.png"), "SpeedBooster"));
        tilesPool.putIfAbsent("Bomberman", new ConstructorTileWrapper("Bomberman",
                "Creature", new Image("/sprites/bomberman.png")));
        tilesPool.putIfAbsent("Slime", new ConstructorTileWrapper("Slime",
                "Creature", new Image("/sprites/slime.png")));
    }

    public void ResizeGrid(int rowsCount, int colsCount){
        List<List<ObservableConstructorTileWrapper>> newGrid = new ArrayList<>();
        for (int i = 0; i < rowsCount; i++)
            newGrid.add(
                    new ArrayList<>(Collections.nCopies(colsCount, null)));
        if (grid != null) {
            for (int i = 1; i < Math.min(newGrid.size(), grid.size() - 1); i++) {
                for (int j = 1; j < Math.min(newGrid.getFirst().size(), grid.getFirst().size() - 1); j++) {
                    if (grid.get(i).get(j) != null) newGrid.get(i).set(j, grid.get(i).get(j));
                }
            }
            for(int i = 0; i < grid.size(); i++) DeleteGridCell(i, grid.getFirst().size()-1);
            for(int j = 0; j < grid.getFirst().size(); j++) DeleteGridCell(grid.size()-1, j);
            for(int i = 0; i < grid.size(); i++){
                for(int j = newGrid.getFirst().size(); j < grid.getFirst().size(); j++){
                    DeleteGridCell(i, j);
                }
            }
            for(int i = newGrid.size(); i < grid.size(); i++){
                for(int j = 0; j < grid.getFirst().size(); j++){
                    DeleteGridCell(i, j);
                }
            }
        }
        grid = newGrid;
        RegisterGrid();
        for (int i = 0; i < grid.size(); i++) {
            SetGridCell(i, 0, tilesPool.get("Metal"));
            SetGridCell(i, grid.getFirst().size() - 1, tilesPool.get("Metal"));
        }
        for (int j = 0; j < grid.getFirst().size(); j++) {
            SetGridCell(0, j, tilesPool.get("Metal"));
            SetGridCell(grid.size() - 1, j, tilesPool.get("Metal"));
        }
    }

    public void SetGridCell(int i, int j, ConstructorTileWrapper tileWrapper){
        DeleteGridCell(i, j);
        if(tileWrapper != null) {
            if (grid.get(i).get(j) != null) grid.get(i).get(j).setWrapper(tileWrapper);
            else grid.get(i).set(j, new ObservableConstructorTileWrapper(tileWrapper));
            RegisterCallback.Apply(i, j, grid);
        }
    }

    private void DeleteGridCell(int i, int j){
        if(grid.get(i).get(j) != null){
            grid.get(i).get(j).setWrapper(null);
        }
    }

    private void RegisterGrid(){
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid.getFirst().size(); j++){
                if(grid.get(i).get(j) != null) RegisterCallback.Apply(i, j, grid);
            }
        }
    }

    public String GetWriteError(){
        if(grid == null) return "Level grid is not set";
        if(writer.getFileNameAppendix() == null) return "File name is not set";
        return null;
     }

    public boolean CheckIfPlacementIsAvailable(int y, int x, ConstructorTileWrapper tile){
        boolean borderPlacement = x == 0 || y == 0 || y == grid.size()-1 || x == grid.getFirst().size()-1;
        boolean validBoosterPlacement = true;
        if(tile.getBoosterName() != null){
            validBoosterPlacement = grid.get(y).get(x) != null && (grid.get(y).get(x).getWrapper().getName() == "Wooden");
        }
        return !borderPlacement && validBoosterPlacement;
    }

    public boolean CheckIfFileDuplicates() {
        return writer.CheckIfFileIsPresent();
    }

    public void SaveLevel(){
        writer.ParseLevelConstructorGrid(grid);
        writer.Write();
    }

    public void SetLevelName(String levelName){
        writer.setFileNameAppendix(levelName+".json");
    }
}


