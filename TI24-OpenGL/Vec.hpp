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
#include <math.h>

class Vec4f
{
public:
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float v[4];
    };
    Vec4f();
    Vec4f(const Vec4f &other);
    Vec4f(float x, float y, float z, float w);
    float& operator [](int);
};

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
    float length();
    void normalize();
    float& operator [](int);
    
    
    Vec3f& operator+=(const Vec3f& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this; // return the result by reference
    }

    friend Vec3f operator+(Vec3f lhs, const Vec3f& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    
    Vec3f& operator-=(const Vec3f& rhs)
    {
        Vec3f inverse = rhs * -1;
        this->operator+=(inverse);
        return *this; // return the result by reference
    }
    
    friend Vec3f operator-(Vec3f lhs, const Vec3f& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    
    Vec3f& operator*=(const float scalar){
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }
    
    friend Vec3f operator*(Vec3f lhs, const float scalar){
        lhs *= scalar;
        return lhs;
    }
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
