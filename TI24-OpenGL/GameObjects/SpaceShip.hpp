//
//  SpaceShip.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef SpaceShip_hpp
#define SpaceShip_hpp

#include <stdio.h>
#include "Vec.hpp"
#include "GameObject.hpp"
#include "SingularGameObject.hpp"


class SpaceShip : public SingularGameObject
{
public:
    SpaceShip(Vec3f position, Vec4f rotation, int scaleFactor);
    void Update(float ticks);
};

#endif /* SpaceShip_hpp */
