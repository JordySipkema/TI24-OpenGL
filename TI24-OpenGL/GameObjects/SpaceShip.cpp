//
//  SpaceShip.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//
#include "SpaceShip.hpp"
#include "Matrix.hpp"

#define SHIP_SPEED 15.0f

SpaceShip::SpaceShip(Vec3f position, Vec4f rotation, float scaleFactor = 1) :
//GameObject(position, rotation, scaleFactor, "models/fightership/13897_Sci-Fi_Fighter_Ship_v1_l1.obj")
    SingularGameObject(position, rotation, scaleFactor, "spacecraft/spacecraft.obj")
{
}

void SpaceShip::Update(float ticks){
    // Bail out;
    if (getParams() == nullptr) { return; }
    
    Vec3f movement = getParams()->movement;
    movement *= (ticks / 1000) * SHIP_SPEED;
    movement = Matrix::Rotate(movement, getParams()->rotation);
    getParams()->position += movement;
}

#undef SHIP_SPEED
