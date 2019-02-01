//
//  EnvironmentSphere.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 28/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//
#define GL_SILENCE_DEPRECATION // Silence the OpenGL/Glut deprecation warnings.

#include "EnvironmentSphere.hpp"
#include <GLUT/GLUT.h>

EnvironmentSphere::EnvironmentSphere(Vec3f position, Vec4f rotation, int scaleFactor = 1)
  : SingularGameObject(position, rotation, scaleFactor, "")
{
}

void EnvironmentSphere::Update(float ticks){ }

void EnvironmentSphere::Draw(void){
    glPushMatrix();
    
    glColor3f(0.0f, 0.4f, 0.0f);
    
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricOrientation(quadric, GLU_INSIDE);
    gluSphere(quadric, (GLdouble)scaleFactor, scaleFactor*50, scaleFactor*50);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glPopMatrix();
}
