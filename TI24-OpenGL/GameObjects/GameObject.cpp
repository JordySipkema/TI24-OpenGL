//
//  GameObject.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#include "GameObject.hpp"
#include "Enumerator.hpp"

GameObject::GameObject(float scaleFactor, std::string model) : scaleFactor(scaleFactor) {
    if (model != ""){
        objModel = new ObjModel(model);
    }
}

GameObject::GameObject(GameObjectParams* initialLocation, float scaleFactor, std::string model) : scaleFactor(scaleFactor) {
    if (model != ""){
        objModel = new ObjModel(model);
    }
    
    Spawn(initialLocation);
}

void GameObject::Spawn(GameObjectParams* params) {
    std::cout << "Spawning GameObject" << std::endl;
    objects.push_back(params);
}

void GameObject::Draw(void) {
    for (const auto &object : objects){
        Draw(object->position, object->rotation);
    }
}

void GameObject::Draw(Vec3f pos, Vec4f rot){
    glPushMatrix();
    
    float scale = 1.0f / scaleFactor;
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rot.w, rot.x, rot.y, rot.z);
    glScalef(scale, scale, scale);
    
    objModel->draw();
    
    glPopMatrix();
}

void GameObject::Update(float ticks) {
    
    auto predicate = [](const GameObjectParams *v) { return v->active == false; };
    
    size_t items = objects.size();
    objects.erase(std::remove_if(objects.begin(), objects.end(), predicate), objects.end());
    size_t removed = items - objects.size();
    if (removed > 0 ) { std::cout << "Removed "<< removed <<" GameObjects" << std::endl;}
};

void GameObject::Destroy(void){
    objects.clear();
}
