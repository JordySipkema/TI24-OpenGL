//
//  AsteroidSpawner.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 31/01/2019.
//  Copyright © 2019 Jordy Sipkema. All rights reserved.
//

#ifndef AsteroidSpawner_hpp
#define AsteroidSpawner_hpp

#define SpawnDistance  300.0f // Distance from center
#define TimeToOrigin    30.0f // Time in seconds to travel to the origin.
#define SpawnInterval    5.0f // time in seconds.

#include <stdio.h>
#include "GameObjectParams.hpp"
#include "GameObjects/GameObject.hpp"

class AsteroidSpawner
{
private:
    bool isStarted = false;
    GameObject* gameObject;
    float spawnDistance = SpawnDistance;
    float internalTicks = 0.0f;
    float speed = spawnDistance / TimeToOrigin;
    
public:
    AsteroidSpawner(GameObject*);
    AsteroidSpawner(GameObject*, float);
    bool ShouldSpawn(float);
    void Spawn(void);
    void SpawnIfNecessary(float);
    void Reset();
    void Start();
    void ResetAndStart();
};

#endif /* AsteroidSpawner_hpp */
