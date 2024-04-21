package com.lab_2_java.Entities.Creatures.Enemies;

import com.lab_2_java.Entities.Creatures.Creature;
import com.lab_2_java.Utility.CollisionChecker;

public abstract class Enemy extends Creature {
    protected Enemy(int speed, CollisionChecker collisionChecker) {
        super(speed, collisionChecker);
    }
}
