//
//  GameObject.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//


#pragma once

#include <stdio.h>
#include <vector>

class GameObject
{
protected:
    Vec3f position;
    
    int scaleFactor;
public:
    virtual void Draw();
    virtual void Update();
};
