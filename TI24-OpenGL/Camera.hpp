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
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

#include <math.h>
#include <future>
#include <iostream>
#include <map>
#include <stack>
//#include "config.h"

class Camera
{
private:
    float eyeposVer = 10.2f; //In vertical plane: y          
    float eyeposHor = 0.0f; //In horizontal plane: x and z
    float cameraCenterX = 0.0f;
    float cameraCenterY = 0.0f;
    float cameraCenterZ = 0.0f;
    
public:
    Camera(void);
    float getEyeposHor(void);
    float getEyeposVer(void);
    float getCameraCenterX(void);
    float getCameraCenterY(void);
    float getCameraCenterZ(void);
    void setEyeposHor(float);
    void setEyeposVer(float);
    void setCameraCenterX(float);
    void setCameraCenterY(float);
    void setCameraCenterZ(float);
};

#endif /* Camera_hpp */
