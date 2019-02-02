//
//  SingularGameObject.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 30/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#include "SingularGameObject.hpp"
#include "Enumerator.hpp"

SingularGameObject::SingularGameObject(Vec3f position, Vec4f rotation, float scaleFactor, std::string model) : GameObject(scaleFactor, model)
{
    GameObjectParams* params = new GameObjectParams(position, rotation);
    Spawn(params);
}

void SingularGameObject::Spawn(GameObjectParams* params)
{
    if (objects.size() >= 1){
        return; // Do not add if we already contain an object; remember that we are singular here?!
    }
    objects.push_back(params);
}

void SingularGameObject::Destroy()
{
    objects.clear(); // Just remove them all
}

void SingularGameObject::Update(float ticks)
{
    if (objects.empty()){
        return; // Nothing to update
    }
    
    //GameObjectParams* location = objects[0];
    // TODO: Do something with the location;
};

GameObjectParams* SingularGameObject::getParams(void){
    if (objects.empty()){
        return nullptr;
    }
    return objects[0];
}
