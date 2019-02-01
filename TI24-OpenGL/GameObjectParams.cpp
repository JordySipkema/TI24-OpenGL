//
//  GameObjectParams.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 29/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#include "GameObjectParams.hpp"

GameObjectParams::GameObjectParams(Vec3f position, Vec4f rotation) : position(position), rotation(rotation)
{
    
}

GameObjectParams::GameObjectParams() : position(Vec3f()), rotation(Vec4f())
{
    
}

GameObjectParams::GameObjectParams(const GameObjectParams &other){
    this->movement = other.movement;
    this->position = other.position;
    this->rotation = other.rotation;
    this->rotationAngle = other.rotationAngle;
    this->distanceTravelled = other.distanceTravelled;
    this->active = other.active;
}
