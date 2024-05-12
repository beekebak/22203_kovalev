package com.lab_2_java.Entities.Tiles.Boosters;

import com.lab_2_java.Entities.Creatures.Bomberman;
import javafx.scene.image.Image;

public class BombCountBooster extends Booster {
    @Override
    public void Boost(Bomberman bomberman){
        bomberman.setBombCount(bomberman.getBombCount()+1);
    }
    public BombCountBooster(){
        super.sprite = new Image("/sprites/BombCountBooster.png");
    }
}
