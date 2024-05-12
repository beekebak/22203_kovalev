package com.lab_2_java.Controllers;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.util.Callback;

import java.net.URL;
import java.util.ResourceBundle;

import static java.lang.Math.max;
import static java.lang.Math.min;

public class MainMenuController implements Initializable {
    @FXML
    Button gameStartButton;
    @FXML
    Label gameName;
    @FXML
    HBox labelHBox;
    @FXML
    HBox startHBox;
    @FXML
    VBox mainVBox;
    @FXML
    HBox constructorHBox;
    @FXML
    Button constructorButton;

    @FXML
    private void StartGame(){
        mainMenuCallback.call(null);
    }

    @FXML
    private void OpenConstructor(){
        constructorCallback.call(null);
    }

    private Callback<Void, Void> mainMenuCallback = new LevelSwitcher.LoadLevelsMenu();
    private Callback<Void, Void> constructorCallback = new LevelSwitcher.LoadConstructor();

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        labelHBox.prefWidthProperty().bind(mainVBox.widthProperty());
        startHBox.prefWidthProperty().bind(mainVBox.widthProperty());
        constructorHBox.prefWidthProperty().bind(mainVBox.widthProperty());
        gameStartButton.widthProperty().addListener(observable -> {
            gameStartButton.fontProperty().setValue(new Font(min(mainVBox.getWidth(), mainVBox.getHeight())/12));
        });
        constructorButton.widthProperty().addListener(observable -> {
            constructorButton.fontProperty().setValue(new Font(min(mainVBox.getWidth(), mainVBox.getHeight())/18));
        });
        gameName.widthProperty().addListener(observable -> {
            gameName.fontProperty().setValue(new Font(min(mainVBox.getWidth(), mainVBox.getHeight())/12));
        });
    }
}
