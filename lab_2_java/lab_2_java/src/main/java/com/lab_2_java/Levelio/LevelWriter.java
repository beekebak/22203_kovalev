package com.lab_2_java.Levelio;

import com.fasterxml.jackson.core.util.DefaultIndenter;
import com.fasterxml.jackson.core.util.DefaultPrettyPrinter;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.lab_2_java.Utility.ObservableConstructorTileWrapper;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class LevelWriter {
    private ObjectMapper mapper = new ObjectMapper().configure(SerializationFeature.INDENT_OUTPUT, true);
    private List<List<SerializableTileWrapper>> serializableTilesGrid = null;

    private String fileNameBase = "src/main/resources/levels/user_levels/";

    private String fileNameAppendix;

    public void setFileNameAppendix(String fileNameAppendix) {
        this.fileNameAppendix = fileNameAppendix;
    }

    public void ParseLevelConstructorGrid(List<List<ObservableConstructorTileWrapper>> grid){
        serializableTilesGrid = new ArrayList<>(grid.size());
        for(int i = 0; i < grid.size(); i++) serializableTilesGrid.add(new ArrayList<>(Collections.
                nCopies(grid.getFirst().size(), null)));
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid.size(); j++){
                if(grid.get(i).get(j) != null){
                    serializableTilesGrid.get(i).set(j, new SerializableTileWrapper(
                            grid.get(i).get(j).getWrapper().getName(), grid.get(i).get(j).getWrapper().getTypeName(),
                            grid.get(i).get(j).getWrapper().getBoosterName()));
                }
            }
        }
    }

    public void Write(){
        File outputFile = new File(fileNameBase+fileNameAppendix);
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
