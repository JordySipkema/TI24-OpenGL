//
//  Asteroid.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 28/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include <stdio.h>
#include <vector>
#include "Vec.hpp"
#include "GameObject.hpp"
#include "GameObjectParams.hpp"


class Asteroid : public GameObject
{
private:
    float maximumDistance = 300.0f;
public:
    Asteroid();
    void Update(float);
};

#endif /* Asteroid_hpp */
