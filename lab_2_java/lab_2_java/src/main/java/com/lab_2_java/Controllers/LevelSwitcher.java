package com.lab_2_java.Controllers;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Modality;
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
            if(!controller.CheckPath(levelLoadingPath)){
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setContentText("level not done yet");
                alert.showAndWait();
                return null;
            }
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
            return null;
        }
    }

    public static class LoadUserLevelsMenu implements Callback <Void, Void> {
        @Override
        public Void call(Void param) {
            Parent userLevelMenu = null;
            try {
                userLevelMenu = FXMLLoader.load(getClass().getResource("/views/UserLevelSelectMenu.fxml"));
            }
            catch (IOException e) {}
            mainStage.getScene().setRoot(userLevelMenu);
            return null;
        }
    }

    public static class LoadLevelEndDialog implements Callback <Void, Void> {
        @Override
        public Void call(Void param){
            Parent levelEndDialog = null;
            try {
                levelEndDialog = FXMLLoader.load(getClass().getResource("/views/LevelEndDialog.fxml"));
            }
            catch (IOException e) {}
            mainStage.getScene().setRoot(levelEndDialog);
            return null;
        }
    }

    public static class LoadMainMenu implements Callback<Void, Void>{
        @Override
        public Void call(Void param){
            Parent mainMenu = null;
            try{
                mainMenu = FXMLLoader.load(getClass().getResource("/views/MainMenu.fxml"));
            }
            catch (IOException e){}
            mainStage.getScene().setRoot(mainMenu);
            return null;
        }
    }

    private static Stage mainStage;
    public LevelSwitcher(Stage stage){
        mainStage = stage;
    }
    public void Start() throws IOException {
        Parent mainMenu = FXMLLoader.load(getClass().getResource("/views/MainMenu.fxml"));
        mainStage.setTitle("Bomberman");
        mainStage.setScene(new Scene(mainMenu));
        mainStage.show();
    }
}
