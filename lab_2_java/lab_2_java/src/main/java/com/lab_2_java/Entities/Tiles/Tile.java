package com.lab_2_java.Entities.Tiles;

import com.lab_2_java.Entities.Entity;
import com.lab_2_java.Utility.SolidityType;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.scene.image.Image;

public abstract class Tile implements Entity {
    protected Image sprite;
    protected SimpleBooleanProperty isBroken = new SimpleBooleanProperty(false);

    public Image getSprite() {
        return sprite;
    }

    public SimpleBooleanProperty isBrokenProperty() {
        return isBroken;
    }

    public abstract SolidityType getSolidity();
}
