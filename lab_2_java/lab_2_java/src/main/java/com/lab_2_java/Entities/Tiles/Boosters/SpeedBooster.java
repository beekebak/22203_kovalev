package com.lab_2_java.Entities.Tiles.Boosters;

import com.lab_2_java.Entities.Creatures.Bomberman;
import javafx.scene.image.Image;

public class SpeedBooster extends Booster{
    @Override
    public void Boost(Bomberman bomberman){
        bomberman.setSpeed(bomberman.getSpeed()+2);
    }
    public SpeedBooster(){
        super.sprite = new Image("/sprites/SpeedBooster.png");
    }
}
