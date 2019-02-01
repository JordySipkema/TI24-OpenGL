//
//  Camera.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <unistd.h>

#include <math.h>
#include <future>
#include <iostream>
#include <map>
#include <stack>

#include "GameObjects/GameObject.hpp"
#include "Vec.hpp"
//#include "config.h"

class Camera
{
private:
    Vec3f position = Vec3f();
    Vec3f lookAt = Vec3f();
    float eyeposVer = 0.2f; //In vertical plane: y          
    float eyeposHor = 0.0f; //In horizontal plane: x and z
    
public:
    Camera();
    float getEyeposHor(void);
    float getEyeposVer(void);
    Vec3f getLookAt(void);
    Vec3f getPosition(void);
    float getCameraCenterX(void);
    float getCameraCenterY(void);
    float getCameraCenterZ(void);
    void setPosition(Vec3f);
    void setLookAt(Vec3f);
    void setCameraCenterX(float);
    void setCameraCenterY(float);
    void setCameraCenterZ(float);
    void setEyeposHor(float);
    void setEyeposVer(float);
};

#endif /* Camera_hpp */
