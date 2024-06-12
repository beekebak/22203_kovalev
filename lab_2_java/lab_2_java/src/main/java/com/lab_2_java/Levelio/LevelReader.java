package com.lab_2_java.Levelio;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.lab_2_java.Entities.Creatures.Bomberman;
import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Entities.EntityFactory;
import com.lab_2_java.Entities.Tiles.BreakableTile;
import com.lab_2_java.Entities.Tiles.Tile;
import com.lab_2_java.Utility.CoordinatesConverter;
import com.lab_2_java.Models.GameLevel;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class LevelReader {
    private final ObjectMapper mapper = new ObjectMapper();
    private SerializableLevel level;
    private List<List<GameLevel.TileWrapper>> gameGrid;
    private List<Creature> enemies;
    private Creature bomberman;
    public LevelReader(String filePath){
        try {
            level = mapper.readValue(new File(filePath), SerializableLevel.class);
            ParseLevel();
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }

    private void ParseLevel(){
        EntityFactory<Tile> tileFactory = new EntityFactory<>("factoryProperties/Tiles");
        EntityFactory<Creature> creaturesFactory = new EntityFactory<>("factoryProperties/Creatures",
                int.class, int.class);
        gameGrid = new ArrayList<>();
        for(int i = 0; i < level.getGrid().size(); i++) gameGrid.add(new ArrayList<>());
        enemies = new ArrayList<>();
        for(int i = 0; i < level.getGrid().size(); i++) {
            for(int j = 0; j < level.getGrid().getFirst().size(); j++){
                if(level.getGrid().get(i).get(j) == null) {
                    gameGrid.get(i).add(j, new GameLevel.TileWrapper(null));
                }
                else if(level.getGrid().get(i).get(j).getType().equals("Tile")){
                    Tile tile = tileFactory.GetInstance(level.getGrid().get(i).get(j).getName());
                    gameGrid.get(i).add(j, new GameLevel.TileWrapper(tile));
                }
                else{
                    Creature creature = creaturesFactory.GetInstance(level.getGrid().get(i).get(j).getName(),
                            CoordinatesConverter.ConvertGridCoordinateToViewCoordinate(j),
                            CoordinatesConverter.ConvertGridCoordinateToViewCoordinate(i));
                    if(creature instanceof Bomberman) bomberman = creature;
                    else enemies.add(creature);
                    gameGrid.get(i).add(j, new GameLevel.TileWrapper(null));
                }
            }
        }
        ParseBoosters(tileFactory);
    }
    private void ParseBoosters(EntityFactory<Tile> factory){
        for(int i = 0; i < level.getGrid().size(); i++) {
            for (int j = 0; j < level.getGrid().getFirst().size(); j++) {
                if(level.getGrid().get(i).get(j) != null && level.getGrid().get(i).get(j).getBoosterName() != null){
                    ((BreakableTile) gameGrid.get(i).get(j).getTile()).setUnderlyingTile(
                            (BreakableTile) factory.GetInstance(level.getGrid().get(i).get(j).getBoosterName()));
                }
            }
        }
    }

    public List<List<GameLevel.TileWrapper>> InitializeGrid(){
        return gameGrid;
    }
    public List<Creature> InitializeEnemies(){
        return enemies;
    }
    public Creature InitializePlayer(){
        return bomberman;
    }

    public static boolean CheckPath(String path) {
        File file = new File(path);
        return file.exists();
    }
}
