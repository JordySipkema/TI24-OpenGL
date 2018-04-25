//
//  Shape.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 25-04-18.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>
#include "Vec3f.hpp"

class Shape {
    
public:
    void static drawCube();
    void static drawCube(Vec3f color);
};

#endif /* Shape_hpp */
