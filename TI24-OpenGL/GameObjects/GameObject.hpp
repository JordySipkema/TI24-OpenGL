//
//  GameObject.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <unistd.h>

#include <math.h>
#include <future>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

#include "Vec.hpp"
#include "../ObjModel.hpp"
#include "GameObjectParams.hpp"

class GameObject
{
//protected:
    
public:
    ObjModel* objModel;
    std::vector<GameObjectParams*> objects;
    
    float collisionRadius;
    int scaleFactor;
    
    GameObject(int scaleFactor, std::string model);
    GameObject(GameObjectParams* initialLocation, int scaleFactor, std::string model);
    
    virtual void Draw(void);
    virtual void Draw(Vec3f position, Vec4f rotation);
    
    virtual void Update(float ticks);
    virtual void Spawn(GameObjectParams*);
};
