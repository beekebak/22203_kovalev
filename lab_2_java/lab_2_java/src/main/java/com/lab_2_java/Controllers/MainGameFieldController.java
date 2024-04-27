package com.lab_2_java.Controllers;

import com.lab_2_java.Utility.GameLevel;
import com.lab_2_java.Utility.MoveDirections;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

import java.net.URL;
import java.util.ResourceBundle;

public class MainGameFieldController implements Initializable{
    @FXML
    Pane fullView;
    @FXML
    Circle camera;
    @FXML
    Canvas backgroundCanvas;

    @FXML
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

    private GameLevel gameLevel = new GameLevel();

    private Scene levelScene;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Rectangle rect = new Rectangle(1, 1);
        rect.xProperty().bindBidirectional(camera.layoutXProperty());
        rect.yProperty().bindBidirectional(camera.layoutYProperty());
        fullView.setClip(rect);
        fullView.translateXProperty().bind(rect.xProperty().multiply(-1));
        fullView.translateYProperty().bind(rect.yProperty().multiply(-1));

        GraphicsContext graphicsContext = backgroundCanvas.getGraphicsContext2D();
        graphicsContext.drawImage(gameLevel.getBackGround(), 0, 0);

        ImageView bomberman = new ImageView(gameLevel.getBomberman().getSprite());
        fullView.getChildren().add(bomberman);
        bomberman.xProperty().bind(gameLevel.getBomberman().getX());
        bomberman.yProperty().bind(gameLevel.getBomberman().getY());

        bomberman.xProperty().addListener((observable, oldValue, newValue) -> {
            double halfSize = levelScene.getWidth()/2;
            if(halfSize < newValue.doubleValue() && newValue.doubleValue() < 5000 - halfSize){
                rect.setX(newValue.doubleValue()-halfSize);
            }
        });
        bomberman.yProperty().addListener((observable, oldValue, newValue) -> {
            double halfSize = levelScene.getHeight()/2;
            if(halfSize < newValue.doubleValue() && newValue.doubleValue() < 2000 - halfSize){
                rect.setY(newValue.doubleValue()-halfSize);
            }
        });

        for(int i = 0; i < gameLevel.getGridXSize(); i++){
            for(int j = 0; j < gameLevel.getGridYSize(); j++){
                if(gameLevel.getCellImage(i, j) != null){
                    ImageView cellView = new ImageView(gameLevel.getCellImage(i,j));
                    fullView.getChildren().add(cellView);
                    cellView.setX(i*48);
                    cellView.setY(j*48);
                    gameLevel.getCellObservable(i,j).addListener(new InvalidationListener() {
                        @Override
                        public void invalidated(Observable observable) {
                            fullView.getChildren().remove(cellView);
                        }
                    });
                }
            }
        }

        levelScene = new Scene(fullView);
        rect.widthProperty().bind(levelScene.widthProperty());
        rect.heightProperty().bind(levelScene.heightProperty());

        levelScene.getRoot().requestFocus();
    }
}
