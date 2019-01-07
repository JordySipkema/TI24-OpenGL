//
//  Camera.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include "Camera.hpp"


Camera::Camera(void)
{
    
}

float Camera::getEyeposHor(void)
{
    return eyeposHor;
}
float Camera::getEyeposVer(void)
{
    return eyeposVer;
}
float Camera::getCameraCenterX(void)
{
    return cameraCenterX;
}
float Camera::getCameraCenterY(void)
{
    return cameraCenterY;
}
float Camera::getCameraCenterZ(void)
{
    return cameraCenterZ;
}
void Camera::setEyeposHor(float newEyeposHor)
{
    eyeposHor = newEyeposHor;
}
void Camera::setEyeposVer(float newEyeposVer)
{
    eyeposVer = newEyeposVer;
}
void Camera::setCameraCenterX(float newCameraCenterX)
{
    cameraCenterX = newCameraCenterX;
}
void Camera::setCameraCenterY(float newCameraCenterY)
{
    cameraCenterY = newCameraCenterY;
}
void Camera::setCameraCenterZ(float newCameraCenterZ)
{
    cameraCenterZ = newCameraCenterZ;
}
