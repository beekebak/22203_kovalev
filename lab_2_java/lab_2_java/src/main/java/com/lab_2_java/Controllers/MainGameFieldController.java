package com.lab_2_java.Controllers;

import com.lab_2_java.Utility.CoordinatesConverter;
import com.lab_2_java.Utility.GameLevel;
import com.lab_2_java.Utility.MoveDirections;
import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

import java.net.URL;
import java.util.ResourceBundle;

import static java.lang.Math.max;

public class MainGameFieldController implements Initializable{
    @FXML
    Pane fullView;
    @FXML
    Circle camera;
    Canvas backgroundCanvas;

    @FXML
    private void HandleKeyEvent(KeyEvent e){
        if(e.getCode() == KeyCode.W || e.getCode() == KeyCode.A || e.getCode() == KeyCode.D || e.getCode() == KeyCode.S){
            MoveCamera(e);
        }
        else if(e.getCode() == KeyCode.SPACE){
            ActionKeyEvent(e);
        }
    }

    private void MoveCamera(KeyEvent e){
        MoveDirections direction = null;
        direction = switch (e.getCode()) {
            case W -> MoveDirections.UP;
            case A -> MoveDirections.LEFT;
            case S -> MoveDirections.DOWN;
            case D -> MoveDirections.RIGHT;
            default -> direction;
        };
        if(direction != null) gameLevel.getBomberman().Move(direction);
    }

    private void ActionKeyEvent(KeyEvent e){
        gameLevel.BombEvent();
    }

    private GameLevel gameLevel = new GameLevel();

    private Scene levelScene;

    private void RegisterTileImageView(int i, int j){
        ImageView cellView = new ImageView(gameLevel.getCellImage(i,j));
        fullView.getChildren().add(cellView);
        cellView.setX(CoordinatesConverter.ConvertGridCoordinateToViewCoordinate(i));
        cellView.setY(CoordinatesConverter.ConvertGridCoordinateToViewCoordinate(j));
        gameLevel.getCellContainmentProperty(i,j).addListener((observable) -> {
            fullView.getChildren().remove(cellView);
        });
    }

    private void RegisterEnemyImageView(int i){
        ImageView cellView = new ImageView(gameLevel.getEnemies().get(i).getSprite());
        fullView.getChildren().add(cellView);
        cellView.xProperty().bind(gameLevel.getEnemies().get(i).getX());
        cellView.yProperty().bind(gameLevel.getEnemies().get(i).getY());
        gameLevel.getEnemies().get(i).IsAlive().addListener((observable) -> {
            fullView.getChildren().remove(cellView);
        });
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Rectangle rect = new Rectangle(1, 1);
        rect.xProperty().bindBidirectional(camera.layoutXProperty());
        rect.yProperty().bindBidirectional(camera.layoutYProperty());
        fullView.setClip(rect);
        fullView.translateXProperty().bind(rect.xProperty().multiply(-1));
        fullView.translateYProperty().bind(rect.yProperty().multiply(-1));

        backgroundCanvas = new Canvas(max(gameLevel.GetXSceneSize(), 1920), max(gameLevel.GetYSceneSize(), 1080));
        fullView.getChildren().add(backgroundCanvas);
        GraphicsContext graphicsContext = backgroundCanvas.getGraphicsContext2D();
        for(int i = 0; i * 5000 < backgroundCanvas.getWidth(); i++){
            for(int j = 0; j * 2000 < backgroundCanvas.getHeight(); j++){
                graphicsContext.drawImage(gameLevel.getBackGround(), i*5000, j*2000);
            }
        }

        ImageView bomberman = new ImageView(gameLevel.getBomberman().getSprite());
        fullView.getChildren().add(bomberman);
        bomberman.xProperty().bind(gameLevel.getBomberman().getX());
        bomberman.yProperty().bind(gameLevel.getBomberman().getY());

        bomberman.xProperty().addListener((observable, oldValue, newValue) -> {
            double halfSize = levelScene.getWidth()/2;
            if(halfSize < newValue.doubleValue() && newValue.doubleValue() < gameLevel.GetXSceneSize() - halfSize){
                rect.setX(newValue.doubleValue()-halfSize);
            }
        });
        bomberman.yProperty().addListener((observable, oldValue, newValue) -> {
            double halfSize = levelScene.getHeight()/2;
            if(halfSize < newValue.doubleValue() && newValue.doubleValue() < gameLevel.GetYSceneSize() - halfSize){
                rect.setY(newValue.doubleValue()-halfSize);
            }
        });

        for(int i = 0; i < gameLevel.GetGridColumnsCount(); i++){
            for(int j = 0; j < gameLevel.GetGridRowsCount(); j++){
                if(gameLevel.getCellImage(i, j) != null){
                    RegisterTileImageView(i, j);
                }
                int effi = i;
                int effj = j;
                gameLevel.getCellContainmentProperty(i, j).addListener(observable -> {
                    RegisterTileImageView(effi, effj);
                });
            }
        }
        for(int i = 0; i < gameLevel.getEnemies().size(); i++){
            int effi = i;
            RegisterEnemyImageView(effi);
        }

        AnimationTimer frameUpdater = new AnimationTimer() {
            @Override
            public void handle(long now) {
                gameLevel.UpdateLevel();
            }
        };
        frameUpdater.start();

        levelScene = new Scene(fullView);
        rect.widthProperty().bind(levelScene.widthProperty());
        rect.heightProperty().bind(levelScene.heightProperty());

        levelScene.getRoot().requestFocus();
        levelScene.getRoot();
    }
}
