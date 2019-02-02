//
//  EnvironmentSphere.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 28/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef EnvironmentSphere_hpp
#define EnvironmentSphere_hpp

#include <stdio.h>
#include "Vec.hpp"
#include "GameObject.hpp"
#include "SingularGameObject.hpp"


class EnvironmentSphere : public SingularGameObject
{
public:
    EnvironmentSphere(Vec3f position, Vec4f rotation, float scaleFactor);
    void Update(float ticks);
    void Draw(void);
};


#endif /* EnvironmentSphere_hpp */
