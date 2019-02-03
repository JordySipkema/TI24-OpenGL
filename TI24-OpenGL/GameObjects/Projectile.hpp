//
//  Projectile.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 30/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <stdio.h>
#include <vector>
#include "Vec.hpp"
#include "GameObject.hpp"
#include "GameObjectParams.hpp"


class Projectile : public GameObject
{
private:
    float maximumDistance = 100.0f;
public:
    Projectile();
    void Update(float);
    void Draw(Vec3f, Vec4f, Vec4f);
};

#endif /* Projectile_hpp */
