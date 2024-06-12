package com.lab_2_java.Controllers;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonBar;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.util.Callback;

import java.net.URL;
import java.util.ResourceBundle;

public class LevelEndDialogController implements Initializable {
    @FXML
    private AnchorPane mainPane;
    @FXML
    private VBox vbox;
    @FXML
    private ButtonBar buttonBox;
    private Callback<Void, Void> levelsMenuCallback = new LevelSwitcher.LoadLevelsMenu();

    private Callback<Void, Void> mainMenuCallback =  new LevelSwitcher.LoadMainMenu();

    @FXML
    private void OpenMenuButtonEvent(){
        mainMenuCallback.call(null);
    }

    @FXML
    private void OpenLevelsMenuButtonEvent(){
        levelsMenuCallback.call(null);
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        vbox.prefWidthProperty().bind(mainPane.widthProperty());
        vbox.prefHeightProperty().bind(mainPane.heightProperty());
        buttonBox.prefWidthProperty().bind(mainPane.widthProperty());
        buttonBox.buttonMinWidthProperty().bind(buttonBox.widthProperty().divide(2));
    }
}
