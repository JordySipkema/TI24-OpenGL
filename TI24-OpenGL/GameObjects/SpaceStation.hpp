//
//  SpaceStation.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 02/02/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef SpaceStation_hpp
#define SpaceStation_hpp

#include <stdio.h>
#include "Vec.hpp"
#include "GameObject.hpp"
#include "SingularGameObject.hpp"

class SpaceStation : public SingularGameObject
{
public:
    SpaceStation(Vec3f position, Vec4f rotation, float scaleFactor);
    void Update(float ticks);
};


#endif /* SpaceStation_hpp */
