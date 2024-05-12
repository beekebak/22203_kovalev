package com.lab_2_java.Controllers;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.io.IOException;

public class LevelSwitcher {
    public static class LoadLevel implements Callback<String, Void> {
        @Override
        public Void call(String levelLoadingPath) {
            Parent level = null;
            MainGameFieldController controller = null;
            try{
                FXMLLoader loader = new FXMLLoader();
                loader.setLocation(getClass().getResource("/views/MainGameField.fxml"));
                level = loader.load();
                controller = loader.getController();
            }
            catch (IOException e) {}
            controller.StartLevel(levelLoadingPath, mainStage.getScene());
            mainStage.getScene().setRoot(level);
            level.requestFocus();
            return null;
        }
    }
    public static class LoadLevelsMenu implements Callback <Void, Void>{
        @Override
        public Void call(Void param){
            Parent levelMenu = null;
            try {
                levelMenu = FXMLLoader.load(getClass().getResource("/views/LevelSelectMenu.fxml"));
            }
            catch (IOException e) {}
            mainStage.getScene().setRoot(levelMenu);
            mainStage.setHeight(mainStage.getScene().getHeight());
            mainStage.setWidth(mainStage.getScene().getWidth());
            return null;
        }
    }

    public static class LoadConstructor implements Callback <Void, Void>{
        @Override
        public Void call(Void param){
            Parent levelConstructor = null;
            try {
                levelConstructor = FXMLLoader.load(getClass().getResource("/views/LevelConstructor.fxml"));
            }
            catch (IOException e) {}
            mainStage.getScene().setRoot(levelConstructor);
            mainStage.setHeight(mainStage.getScene().getHeight());
            mainStage.setWidth(mainStage.getScene().getWidth());
            return null;
        }
    }

    public static class LoadUserLevelsMenu implements Callback <Void, Void> {
        @Override
        public Void call(Void param) {
            return null;
        }
    }

    private static Stage mainStage;
    public LevelSwitcher(Stage stage){
        mainStage = stage;
    }
    public void Start() throws IOException {
        Parent mainMenu = FXMLLoader.load(getClass().getResource("/views/MainMenu.fxml"));
        //Parent mainMenu = FXMLLoader.load(getClass().getResource("/views/LevelConstructor.fxml"));
        mainStage.setTitle("Bomberman");
        mainStage.setScene(new Scene(mainMenu));
        mainStage.show();
    }
}
