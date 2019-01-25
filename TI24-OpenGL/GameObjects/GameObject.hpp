//
//  GameObject.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//
#pragma once

#include <stdio.h>
#include "Vec.hpp"
#include "../ObjModel.hpp"

#include <GLUT/GLUT.h>
#include <unistd.h>

#include <math.h>
#include <future>
#include <iostream>
#include <map>
#include <stack>

class GameObject
{
//protected:
    
public:
    ObjModel* objModel;
    Vec3f position; // x,y,z
    Vec4f rotation; // x,y,z
    int scaleFactor;
    
    GameObject(Vec3f position, Vec4f rotation, int scaleFactor, std::string model);
    
    void Draw(void);
    
    virtual void Update(double ticks) {};
};
