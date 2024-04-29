package com.lab_2_java.Levelio;

import com.fasterxml.jackson.core.util.DefaultIndenter;
import com.fasterxml.jackson.core.util.DefaultPrettyPrinter;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class LevelWriter {
    private ObjectMapper mapper = new ObjectMapper().configure(SerializationFeature.INDENT_OUTPUT, true);
    private List<List<SerializableTileWrapper>> serializableTilesGrid = null;

    private String fileName = "src/main/resources/levels/campaign_levels/level1-1.json";

    private void AddCrates(List<List<SerializableTileWrapper>> serializableGrid){
        for(int i = 1; i < 11; i++){
            serializableGrid.get(i).set(2, new SerializableTileWrapper("Wooden", "Tile"));
            serializableGrid.get(i).set(4, new SerializableTileWrapper("Wooden", "Tile"));
            serializableGrid.get(i).set(7, new SerializableTileWrapper("Wooden", "Tile"));
        }
    }

    private void AddBomberman(List<List<SerializableTileWrapper>> serializableGrid){
        serializableGrid.get(3).set(3, new SerializableTileWrapper("Bomberman", "Creature"));
    }
    private void AddEnemies(List<List<SerializableTileWrapper>> serializableGrid){
        serializableGrid.get(1).set(1, new SerializableTileWrapper("Slime", "Creature"));
        serializableGrid.get(5).set(5, new SerializableTileWrapper("Slime", "Creature"));
        serializableGrid.get(4).set(8, new SerializableTileWrapper("Slime", "Creature"));
    }

    private void CreateSerializableGrid(int rows, int columns){
        List<List<SerializableTileWrapper>> newSerializableGrid = new ArrayList<>();
        for(int i = 0; i < rows; i++) newSerializableGrid.add(new ArrayList<SerializableTileWrapper>(
                Collections.nCopies(columns, null)));
        for(int i = 0; i < rows; i++){
            newSerializableGrid.get(i).set(0, new SerializableTileWrapper("Metal", "Tile"));
            newSerializableGrid.get(i).set(columns-1, new SerializableTileWrapper("Metal", "Tile"));
        }
        for(int i = 0; i < columns; i++){
            newSerializableGrid.get(0).set(i, new SerializableTileWrapper("Metal", "Tile"));
            newSerializableGrid.get(rows-1).set(i, new SerializableTileWrapper("Metal", "Tile"));
        }
        if(serializableTilesGrid != null){
            for(int i = 1; i < serializableTilesGrid.size()-1; i++){
                for(int j = 0; j < serializableTilesGrid.get(0).size()-1; j++){
                    if(serializableTilesGrid.get(i).get(j) != null) {
                        newSerializableGrid.get(i).set(j, serializableTilesGrid.get(i).get(j));
                    }
                }
            }
        }
        AddCrates(newSerializableGrid);
        AddBomberman(newSerializableGrid);
        AddEnemies(newSerializableGrid);
        serializableTilesGrid = newSerializableGrid;
    }


    public void Write(){
        CreateSerializableGrid(12, 10);
        File outputFile = new File(fileName);
        try{
            mapper.enable(SerializationFeature.INDENT_OUTPUT);
            DefaultPrettyPrinter prettyPrinter = new DefaultPrettyPrinter();
            prettyPrinter.indentArraysWith(DefaultIndenter.SYSTEM_LINEFEED_INSTANCE);
            mapper.writer(prettyPrinter).writeValue(outputFile, new SerializableLevel(serializableTilesGrid));
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
}
