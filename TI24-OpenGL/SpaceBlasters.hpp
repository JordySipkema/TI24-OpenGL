//
//  SpaceBlasters.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef SpaceBlasters_hpp
#define SpaceBlasters_hpp

#define GL_SILENCE_DEPRECATION // Silence the OpenGL/Glut deprecation warnings.


#include <stdio.h>
#include <vector>
#include <GLUT/glut.h>
#include "glm/glm.hpp"
#include "Keyboard.hpp"
#include "Camera.hpp"
#include "AsteroidSpawner.hpp"
#include "GameObjects/GameObject.hpp"
#include "GameObjects/SingularGameObject.hpp"
#include "GameObjects/Asteroid.hpp"

class SpaceBlasters
{
private:
    //Fields
    AsteroidSpawner* spawner;
    bool leftCannon = false;
    bool followCam = true;
    float angle = 0.0f;
    
    
    //Methods
    void updateCamera(void);
    void handleKeyboard(double);
    void spawnAsteroid(void);
    void shootProjectile(void);
    void collisionDetection(void);
    
    
public:
    Keyboard* keyboard;
    Camera* camera;
    SingularGameObject* spaceship;
    SingularGameObject* environment;
    GameObject* asteroids;
    GameObject* projectiles;
    
    SpaceBlasters(Camera*, Keyboard*);
    
    void initGame(void);
    
    void draw(void);
    void update(double ticks);
};


#endif /* SpaceBlasters_hpp */
