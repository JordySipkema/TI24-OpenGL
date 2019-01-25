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


class SpaceShip : public GameObject
{
public:
    SpaceShip(Vec3f position, Vec4f rotation, int scaleFactor);
    void Update(double ticks);
};

#endif /* SpaceShip_hpp */
