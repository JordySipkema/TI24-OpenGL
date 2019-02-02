//
//  AsteroidSpawner.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 31/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//
#define AsRadian(x) ((x)*(M_PI/180.0f))
#include "AsteroidSpawner.hpp"

#include <random>
AsteroidSpawner::AsteroidSpawner(GameObject* object){
    this->gameObject = object;
}

AsteroidSpawner::AsteroidSpawner(GameObject* object, float distance){
    this->gameObject = object;
    this->spawnDistance = distance;
    this->speed = distance / TimeToOrigin;
}

void AsteroidSpawner::Start(void){
    isStarted = true;
}

void AsteroidSpawner::Reset(void){
    isStarted = false;
    internalTicks = 0.0f;
}

void AsteroidSpawner::ResetAndStart(void){
    Reset(); Start();
}

bool AsteroidSpawner::ShouldSpawn(float ticks){
    // We cant spawn if we are not enabled
    if (!isStarted) { return false; }
    
    
    internalTicks += ticks;
    if (internalTicks >= (1000 * SpawnInterval)){
        return true;
    }
    return false;
}

void AsteroidSpawner::Spawn(void) {
    // If you are calling this while not started; I dont care...
    // We are spawning right now; so reset the ticks:
    internalTicks = 0.0f;
    
    GameObjectParams* params = new GameObjectParams();
    params->active = true;
    
    // Position:
    float angle = rand() % 360; // Spawn anywhere...
    // Use only x and z (2D) for now:
    params->position = Vec3f(spawnDistance * sin(AsRadian(angle)), 0, spawnDistance * cos(AsRadian(angle)));
    
    // Direction:
    // Normalize the vector (make length = 1) and multiply by negative speed
    // By using a negative value; the inverse vector is used (pointing inwards)
    Vec3f dir = Vec3f(params->position);
    dir.normalize();
    dir *= -speed;
    params->movement = dir;
    
    // Rotation:
    // Rotate around a random vector; just for fun.
    params->rotation = Vec4f(rand() % 4, rand() % 4, rand() % 4, 0.0f);
    
    gameObject->Spawn(params);
}

void AsteroidSpawner::SpawnIfNecessary(float ticks) {
    if (ShouldSpawn(ticks)){
        Spawn();
    }
}
