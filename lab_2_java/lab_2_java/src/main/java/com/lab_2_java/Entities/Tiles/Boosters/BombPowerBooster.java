package com.lab_2_java.Entities.Tiles.Boosters;

import com.lab_2_java.Entities.Creatures.Bomberman;
import javafx.scene.image.Image;

public class BombPowerBooster extends Booster{
    @Override
    public void Boost(Bomberman bomberman){
        bomberman.setBombPower(bomberman.getBombPower()+1);
    }
    public BombPowerBooster(){
        super.sprite = new Image("/sprites/BombPowerBooster.png");
    }
}
