//
//  Vec.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 19/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include "Vec.hpp"

Vec4f::Vec4f(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
Vec4f::Vec4f()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}
Vec4f::Vec4f(const Vec4f &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
}

float& Vec4f::operator [](int index)
{
    return v[index];
}



Vec3f::Vec3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
Vec3f::Vec3f()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
Vec3f::Vec3f(const Vec3f &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

float Vec3f::length(){
    return sqrt((x*x)+(y*y)+(z*z));
}

void Vec3f::normalize(){
    float length = this->length();
    
    if (length == 0){ return; } // avoid division by zero.
    this->operator*=(1 / this->length());
}

float& Vec3f::operator [](int index)
{
    return v[index];
}



Vec2f::Vec2f(float x, float y)
{
    this->x = x;
    this->y = y;
}
Vec2f::Vec2f()
{
    this->x = 0;
    this->y = 0;
}
Vec2f::Vec2f(const Vec2f &other)
{
    this->x = other.x;
    this->y = other.y;
}

float& Vec2f::operator [](int index)
{
    return v[index];
}
