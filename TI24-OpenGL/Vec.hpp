//
//  Vec.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 19/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef Vec_hpp
#define Vec_hpp

#include <stdio.h>
#include <iostream>

class Vec3f
{
public:
    union
    {
        struct
        {
            float x, y, z;
        };
        float v[3];
    };
    Vec3f();
    Vec3f(const Vec3f &other);
    Vec3f(float x, float y, float z);
    float& operator [](int);
};

class Vec2f
{
public:
    union
    {
        struct
        {
            float x, y;
        };
        float v[2];
    };
    Vec2f();
    Vec2f(float x, float y);
    Vec2f(const Vec2f &other);
    float& operator [](int);
};

#endif /* Vec_hpp */
