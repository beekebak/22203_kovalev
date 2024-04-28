package com.lab_2_java.Levelio;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.lab_2_java.Entities.EntityFactory;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Entities.Tiles.Tile;
import com.lab_2_java.Utility.GameLevel;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class LevelReader {
    private final ObjectMapper mapper = new ObjectMapper();
    private SerializableLevel level;
    public LevelReader(String filePath){
        try {
            level = mapper.readValue(new File(filePath), SerializableLevel.class);
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }

    private void RegisterTile(List<List<GameLevel.TileWrapper>> gameGrid, Tile tile, int i, int j){
        if(tile instanceof BreakableTile){
            tile.isBrokenProperty().addListener(observable -> {
                gameGrid.get(i).get(j).setTile(null);
            });
        }
    }

    public List<List<GameLevel.TileWrapper>> InitializeGrid(){
        EntityFactory<Tile> tileFactory = new EntityFactory<>("factoryProperties/Tiles");
        List<List<GameLevel.TileWrapper>> gameGrid = new ArrayList<>();
        for(int i = 0; i < level.getGrid().size(); i++){
            gameGrid.add(new ArrayList<>());
        }
        for(int i = 0; i < level.getGrid().size(); i++) {
            for(int j = 0; j < level.getGrid().getFirst().size(); j++){
                if(level.getGrid().get(i).get(j) == null) {
                    gameGrid.get(i).add(j, new GameLevel.TileWrapper(null));
                }
                else{
                    Tile tile = tileFactory.GetInstance(level.getGrid().get(i).get(j));
                    gameGrid.get(i).add(j, new GameLevel.TileWrapper(tile));
                    RegisterTile(gameGrid, tile, i, j);
                }
            }
        }
        return gameGrid;
    }
    public void InitializeEnemies(){

    }
    public void InitializePlayer(){

    }
    public void InitializeBackground(){

    }
}
