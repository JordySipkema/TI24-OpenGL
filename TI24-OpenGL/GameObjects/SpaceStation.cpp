//
//  SpaceStation.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 02/02/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#include "SpaceStation.hpp"
#include "SingularGameObject.hpp"

SpaceStation::SpaceStation(Vec3f position, Vec4f rotation, float scaleFactor = 0.25f) :
SingularGameObject(position, rotation, scaleFactor, "models/spacestation/model_low.obj")
{
    collisionRadius = (1.0f / scaleFactor) - 1;
}

void SpaceStation::Update(float ticks){
    GameObjectParams* params = SingularGameObject::getParams();
    
    if (params == nullptr){
        return; //abort
    }
    
    params->rotation.w += (ticks / 1000) * 10;
}
