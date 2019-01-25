//
//  SpaceShip.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include "SpaceShip.hpp"

SpaceShip::SpaceShip(Vec3f position, Vec4f rotation, int scaleFactor = 1) :
//GameObject(position, rotation, scaleFactor, "models/fightership/13897_Sci-Fi_Fighter_Ship_v1_l1.obj")
    GameObject(position, rotation, scaleFactor, "spacecraft/spacecraft.obj")
{
}

void SpaceShip::Update(double ticks){
    rotation.w += ticks / 40;
}
