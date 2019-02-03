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
#define sb_HEALTH            100
#define sb_ASTEROID_DAMAGE     5
#define sb_SHIP_DAMAGE        10
#define sb_PROJECTILE_DAMAGE  10

#define sb_GAMESTATE_NOGAME   0
#define sb_GAMESTATE_PLAYING  1
#define sb_GAMESTATE_PAUSED   2
#define sb_GAMESTATE_GAMEOVER 3

#include <stdio.h>
#include <vector>
#include <GLUT/glut.h>
#include "glm/glm.hpp"
#include "Keyboard.hpp"
#include "Camera.hpp"
#include "AsteroidSpawner.hpp"
#include "GameObjects/GameObject.hpp"
#include "GameObjects/SingularGameObject.hpp"
#include "Texthelper.hpp"

class SpaceBlasters
{
private:
    //Fields
    AsteroidSpawner* spawner;
    bool leftCannon = false;
    bool followCam = true;
    float angle = 0.0f;
    int health = sb_HEALTH;
    unsigned short gamestate = sb_GAMESTATE_NOGAME;
    
    
    //Methods
    void updateCamera(void);
    void handleKeyboard(double);
    void spawnAsteroid(void);
    void shootProjectile(void);
    void collisionDetection(void);
    void restart(void);
    void stopGame(void);
    
    
public:
    Keyboard* keyboard;
    Camera* camera;
    SingularGameObject* spacestation;
    SingularGameObject* spaceship;
    SingularGameObject* environment;
    GameObject* asteroids;
    GameObject* projectiles;
    
    SpaceBlasters(Camera*, Keyboard*);
    
    void initGame(void);
    
    void draw(void);
    void drawHud(void);
    void update(double ticks);
};

#endif /* SpaceBlasters_hpp */
