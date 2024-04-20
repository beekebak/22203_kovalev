package com.lab_2_java.Controllers;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
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
    private void MoveCamera(){
        camera.setLayoutX(camera.getLayoutX()+100);
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Rectangle rect = new Rectangle(400, 200);
        rect.xProperty().bind(camera.layoutXProperty());
        rect.yProperty().bind(camera.layoutYProperty());
        fullView.setClip(rect);
    }
}
