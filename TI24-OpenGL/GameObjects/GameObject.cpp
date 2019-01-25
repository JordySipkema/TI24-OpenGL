//
//  GameObject.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject(Vec3f position, Vec4f rotation, int scaleFactor, std::string model) : position(position), rotation(rotation), scaleFactor(scaleFactor) {
    objModel = new ObjModel(model);
}

void GameObject::Draw(void){
    glPushMatrix();
    
    float scale = 1.0f / scaleFactor;
    glScalef(scale, scale, scale);
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.w, rotation.x, rotation.y, rotation.z);
    objModel->draw();
    
    glPopMatrix();
}
