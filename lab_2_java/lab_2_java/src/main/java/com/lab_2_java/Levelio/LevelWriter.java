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

    private List<List<String>> serializableGrid = null;
    private String fileName = "src/main/resources/levels/campaign_levels/level1-1.json";

    private void AddCrates(List<List<String>> serializableGrid){
        for(int i = 1; i < 11; i++){
            serializableGrid.get(i).set(2, "Wooden");
            serializableGrid.get(i).set(4, "Wooden");
            serializableGrid.get(i).set(7, "Wooden");
        }
    }

    private void CreateSerializableGrid(int rows, int columns){
        List<List<String>> newSerializableGrid = new ArrayList<>();
        for(int i = 0; i < rows; i++) newSerializableGrid.add(new ArrayList<String>(
                Collections.nCopies(columns, null)));
        for(int i = 0; i < rows; i++){
            newSerializableGrid.get(i).set(0, "Metal");
            newSerializableGrid.get(i).set(columns-1, "Metal");
        }
        for(int i = 0; i < columns; i++){
            newSerializableGrid.get(0).set(i, "Metal");
            newSerializableGrid.get(rows-1).set(i, "Metal");
        }
        if(serializableGrid != null){
            for(int i = 1; i < serializableGrid.size()-1; i++){
                for(int j = 0; j < serializableGrid.get(0).size()-1; j++){
                    if(serializableGrid.get(i).get(j) != null) {
                        newSerializableGrid.get(i).set(j, serializableGrid.get(i).get(j));
                    }
                }
            }
        }
        //AddCrates(newSerializableGrid);
        serializableGrid = newSerializableGrid;
    }

    public static class SerializableGrid{
        public List<List<String>> serializableGrid;
        public SerializableGrid(List<List<String>> serializableGrid){
            this.serializableGrid = serializableGrid;
        }
    }
    public void Write(){
        CreateSerializableGrid(12, 10);
        File outputFile = new File(fileName);
        try{
            mapper.enable(SerializationFeature.INDENT_OUTPUT);
            DefaultPrettyPrinter prettyPrinter = new DefaultPrettyPrinter();
            prettyPrinter.indentArraysWith(DefaultIndenter.SYSTEM_LINEFEED_INSTANCE);
            mapper.writer(prettyPrinter).writeValue(outputFile, new SerializableLevel(serializableGrid));
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

    public List<List<String>> getSerializableGrid() {
        return serializableGrid;
    }
}
