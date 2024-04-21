package com.lab_2_java.Utility;

import com.lab_2_java.Entities.Creatures.Bomberman;
import javafx.scene.image.Image;

public class GameLevel {
    private Image backGround = new Image("/sprites/background.png");
    private Bomberman bomberman = new Bomberman();
    public Image getBackGround() {
        return backGround;
    }
    public Bomberman getBomberman(){
        return bomberman;
    }
}
