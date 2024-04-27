package com.lab_2_java.Entities;

import javafx.scene.image.Image;

public interface Entity {
     Image getSprite();

     void HandleCollision(Entity collided);
}
