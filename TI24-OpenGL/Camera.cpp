//
//  Camera.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera() { }

float Camera::getEyeposHor(void) { return eyeposHor; }
float Camera::getEyeposVer(void) { return eyeposVer; }

Vec3f Camera::getPosition(void) { return position; }
Vec3f Camera::getLookAt(void) { return lookAt; }
float Camera::getCameraCenterX(void) { return position.x; }
float Camera::getCameraCenterY(void) { return position.y; }
float Camera::getCameraCenterZ(void) { return position.z; }


void Camera::setEyeposHor(float newEyeposHor) { eyeposHor = newEyeposHor; }
void Camera::setEyeposVer(float newEyeposVer) { eyeposVer = newEyeposVer; }

void Camera::setPosition(Vec3f newPosition) { position = newPosition; }
void Camera::setLookAt(Vec3f newLookAt) { lookAt = newLookAt; }
void Camera::setCameraCenterX(float newCameraCenterX) { position.x = newCameraCenterX; }
void Camera::setCameraCenterY(float newCameraCenterY) { position.y = newCameraCenterY; }
void Camera::setCameraCenterZ(float newCameraCenterZ) { position.z = newCameraCenterZ; }
