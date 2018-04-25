//
//  Vec3f.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 25-04-18.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef Vec3f_hpp
#define Vec3f_hpp

#include <stdio.h>

struct Vec3f {
    float x;
    float y;
    float z;
    
public:
    Vec3f(): x(0.0f), y(0.0f), z(0.0f) { };
    Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};
};

#endif /* Vec3f_hpp */
