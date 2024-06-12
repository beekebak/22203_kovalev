package com.lab_2_java.Controllers;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.util.Callback;

import java.io.File;
import java.net.URL;
import java.util.ResourceBundle;

import static java.lang.Math.min;

public class UserLevelSelectMenuController implements Initializable {
    @FXML
    private VBox levelContainer;
    @FXML
    private ScrollPane mainScrollPane;

    Callback<String, Void> startLevelCallback = new LevelSwitcher.LoadLevel();

    Callback<Void, Void> backToCampaingLevelsCallback = new LevelSwitcher.LoadLevelsMenu();

    @FXML
    private void LoadLevelsMenu(){
        backToCampaingLevelsCallback.call(null);
    }

    private void UserLevelButtonEvent(String name){
        startLevelCallback.call("src/main/resources/levels/user_levels/"+name+".json");
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        levelContainer.prefWidthProperty().bind(mainScrollPane.widthProperty());
        File userLevels = new File("src/main/resources/levels/user_levels");
        for(File child:userLevels.listFiles()){
            String name = child.getName().replace(".json", "");
            Button userLevelSelectButton = new Button(name);
            userLevelSelectButton.prefWidthProperty().bind(levelContainer.widthProperty().divide(2));
            userLevelSelectButton.prefHeightProperty().bind(levelContainer.heightProperty().divide(6));
            userLevelSelectButton.setOnAction(event -> {
                UserLevelButtonEvent(name);
            });
            userLevelSelectButton.widthProperty().addListener(observable -> {
                userLevelSelectButton.fontProperty().setValue(new
                        Font(min(levelContainer.getWidth(),
                        levelContainer.getHeight())/12));
            });
            levelContainer.getChildren().add(userLevelSelectButton);
            userLevelSelectButton.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        }
    }
}
