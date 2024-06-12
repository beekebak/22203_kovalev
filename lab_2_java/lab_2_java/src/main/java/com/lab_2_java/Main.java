package com.lab_2_java;

import com.lab_2_java.Controllers.LevelSwitcher;
import javafx.application.Application;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        stage.setMinHeight(600);
        stage.setMinWidth(800);
        stage.setFullScreen(true);
        LevelSwitcher switcher = new LevelSwitcher(stage);
        switcher.Start();
    }
    public static void main(String[] args) {
        launch();
    }
}