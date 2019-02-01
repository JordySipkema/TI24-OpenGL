//
//  SingularGameObject.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 30/01/2019.
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

#include "GameObject.hpp"
#include "GameObjectParams.hpp"
#include "Vec.hpp"
#include "../ObjModel.hpp"



class SingularGameObject : public GameObject
{
    
public:
    
    SingularGameObject(Vec3f position, Vec4f rotation, int scaleFactor, std::string model);
    
    virtual void Update(float ticks);
    virtual void Spawn(GameObjectParams*);
    virtual void Destroy();
    
    GameObjectParams* getParams(void);
};
