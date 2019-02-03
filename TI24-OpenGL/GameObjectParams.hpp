//
//  GameObjectLocation.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 29/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef GameObjectParams_hpp
#define GameObjectParams_hpp

#include <stdio.h>
#include "Vec.hpp"


class GameObjectParams
{
    //protected:
    
public:
    Vec3f movement; // Vector describing direction of movement
    Vec3f position; // Vector describing position of the GameObject
    Vec4f rotation; // 4D-Vector describing rotation-vector (x,y,z) and w (rotation around that vector)
    Vec4f effect;   // 4D-Vector describing a visual effect.

    float rotationAngle = 0.0f;
    float distanceTravelled = 0.0f;
    bool active = true;
    
    GameObjectParams(void);
    GameObjectParams(Vec3f position, Vec4f rotation);
    GameObjectParams(const GameObjectParams &other);
};


#endif /* GameObjectParams_hpp */
