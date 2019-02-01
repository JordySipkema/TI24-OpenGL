//
//  Asteroid.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 28/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//
#define GL_SILENCE_DEPRECATION // Silence the OpenGL/Glut deprecation warnings.
#define AsRadian(x) ((x)*(M_PI/180.0f))
#define _USE_MATH_DEFINES

#include "Asteroid.hpp"

Asteroid::Asteroid() : GameObject(90, "models/asteroid/asteroid_low.obj")
{
    collisionRadius = 3.0f;
}

void Asteroid::Update(float ticks){
    GameObject::Update(ticks);
    
    for (const auto &object : objects) {
        Vec3f temp = object->movement;
        temp *= ticks / 1000.0f;
        object->distanceTravelled += temp.length();
        object->position += temp;
        
        if (object->distanceTravelled >= maximumDistance - collisionRadius){
            object->active = false;
        }
        
        object->rotation.w += ticks / 40;
    }
}
