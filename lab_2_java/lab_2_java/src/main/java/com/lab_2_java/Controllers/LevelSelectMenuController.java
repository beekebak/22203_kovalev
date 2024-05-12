package com.lab_2_java.Controllers;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.util.Callback;

import java.net.URL;
import java.util.ResourceBundle;

import static java.lang.Math.min;


public class LevelSelectMenuController implements Initializable {
    @FXML
    GridPane grid;
    @FXML
    Button userLevelsButton;
    @FXML
    VBox mainVBox;

    Callback<String, Void> startLevelCallback = new LevelSwitcher.LoadLevel();
    Callback<Void, Void> loadUserLevelsMenuCallback = new LevelSwitcher.LoadUserLevelsMenu();
    @FXML
    private void UserLevelsButtonEvent(){
        loadUserLevelsMenuCallback.call(null);
    }

    private void CampaignLevelButtonEvent(String name){
        startLevelCallback.call("src/main/resources/levels/campaign_levels/"+name+".json");
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        grid.prefWidthProperty().bind(mainVBox.widthProperty().divide(4).multiply(3));
        grid.prefHeightProperty().bind(mainVBox.heightProperty().divide(4).multiply(3));
        userLevelsButton.prefWidthProperty().bind(mainVBox.widthProperty().divide(4).multiply(3));
        userLevelsButton.widthProperty().addListener(observable -> {
            userLevelsButton.fontProperty().setValue(new Font(min(grid.getWidth(), grid.getHeight())/20));
        });
        for(int i = 0; i < grid.getColumnCount(); i++){
            for(int j = 0; j < grid.getRowCount(); j++){
                Button campaingLevelSelectButton = new Button("level" + (j+1) + "-" + (i+1));
                campaingLevelSelectButton.setOnAction(event -> {
                    CampaignLevelButtonEvent(campaingLevelSelectButton.textProperty().get());
                });
                campaingLevelSelectButton.widthProperty().addListener(observable -> {
                    campaingLevelSelectButton.fontProperty().setValue(new
                            Font(min(grid.getWidth(),
                                 grid.getHeight())/20));
                });
                grid.add(campaingLevelSelectButton, i, j);
                campaingLevelSelectButton.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
            }
        }
    }
}
