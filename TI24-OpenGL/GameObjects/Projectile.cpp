//
//  Projectile.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 30/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//
#define GL_SILENCE_DEPRECATION // Silence the OpenGL/Glut deprecation warnings.
#define AsRadian(x) ((x)*(M_PI/180.0f))
#define _USE_MATH_DEFINES
#define PROJECTILE_SPEED 40.0f

#include "Projectile.hpp"


Projectile::Projectile() : GameObject(4, "")
{
    collisionRadius = 0.5f;
}

void Projectile::Draw(Vec3f position, Vec4f rotation, Vec4f effect){
    glPushMatrix();
    
    float height = 1.25f;
    float radius = 0.15f;
    
    glColor3f(1.0f, 1.0f, 0.0f); //Yellow?
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.w, rotation.x, rotation.y, rotation.z);
    
    GLUquadricObj *quadratic = gluNewQuadric();
    gluCylinder(quadratic, radius, radius, height, 32, 32);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void Projectile::Update(float ticks){
    GameObject::Update(ticks);
    
    for (const auto &object : objects){
        Vec3f temp = object->movement;
        temp *= ticks / 1000 * PROJECTILE_SPEED;
        object->distanceTravelled += temp.length();
        object->position += temp;
        
        if (object->distanceTravelled > maximumDistance) {
            object->active = false; // Remove it next cycle;
        }
    }
}

#undef PROJECTILE_SPEED
