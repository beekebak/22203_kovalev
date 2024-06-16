package com.lab_2_java.TileWrappers;

import javafx.scene.image.Image;

public class ConstructorTileWrapper {
    private String name;
    private String typeName;
    private String boosterName = null;
    private Image image;

    public ConstructorTileWrapper(String name, String typeName, Image image, String boosterName) {
        this.name = name;
        this.typeName = typeName;
        this.image = image;
        this.boosterName = boosterName;
    }
    public ConstructorTileWrapper(String name, String typeName, Image image) {
        this(name, typeName, image, null);
    }

    public String getName() {
            return name;
        }

    public String getTypeName() {
            return typeName;
        }

    public Image getImage() {
            return image;
        }

    public String getBoosterName() {
        return boosterName;
    }

    public void setBoosterName(String boosterName) {
        this.boosterName = boosterName;
    }
}
