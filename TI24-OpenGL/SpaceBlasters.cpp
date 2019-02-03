//
//  SpaceBlasters.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//
#define AsRadian(x) ((x)*(M_PI/180.0f))
#define _USE_MATH_DEFINES

#define default_camera_position Vec3f(0,0,-15)
#define default_camera_rotation Vec4f(0,1,0,0)
#define spaceship_initial_position Vec3f(0,0,-20)
#define spaceship_initial_rotation Vec4f(0,1,0,50)
#define spaceship_tilt_max_angle 25.0f

#include <cmath>
#include <cstdlib>
#include <sstream>
#include "SpaceBlasters.hpp"
#include "Matrix.hpp"
#include "GameObjects/SpaceStation.hpp"
#include "GameObjects/SpaceShip.hpp"
#include "GameObjects/EnvironmentSphere.hpp"
#include "GameObjects/Asteroid.hpp"
#include "GameObjects/Projectile.hpp"



SpaceBlasters::SpaceBlasters(Camera* camera, Keyboard* keyboard) : camera(camera), keyboard(keyboard) { }

void SpaceBlasters::initGame(void) {
    environment  = new EnvironmentSphere(Vec3f(), Vec4f(), 950);
    spacestation = new SpaceStation(Vec3f(), Vec4f(0,1,0,0), 0.125f);
    spaceship    = new SpaceShip(spaceship_initial_position, spaceship_initial_rotation, 8);
    asteroids    = new Asteroid();
    projectiles  = new Projectile();
    spawner      = new AsteroidSpawner(asteroids);
    
    updateCamera();
    spaceship->Destroy();
    //spawner->Start();
}

void SpaceBlasters::stopGame(void){
    spaceship->Destroy();
    asteroids->Destroy();
    projectiles->Destroy();
    spawner->Reset();
}

void SpaceBlasters::restart(void){
    health = sb_HEALTH;
    
    // Destroy phase: remove everything
    stopGame();
    
    // Reset phase: reset everything for a new game
    spawner->Reset();
    GameObjectParams* params = new GameObjectParams(spaceship_initial_position, spaceship_initial_rotation);
    params->effect = Vec4f(0, 0, 1, 0);
    spaceship->Spawn(params);
    spawner->Start();
}

void SpaceBlasters::draw(void)
{
    updateCamera();
    //Reposition the environment around spaceship.
    if (spaceship->getParams() == nullptr) {
        environment->getParams()->position = Vec3f();
    } else {
        environment->getParams()->position = spaceship->getParams()->position;
    }
    
    
    environment->Draw();
    spacestation->Draw();
    spaceship->Draw();
    asteroids->Draw();
    projectiles->Draw();
}

void SpaceBlasters::update(double ticks)
{
    handleKeyboard(ticks);
    updateCamera();

    spacestation->Update(ticks);
    spaceship->Update(ticks);
    environment->Update(ticks);
    
    asteroids->Update(ticks);
    projectiles->Update(ticks);
    
    collisionDetection();
    spawner->SpawnIfNecessary(ticks);
    if (health <= 0){
        gamestate = sb_GAMESTATE_GAMEOVER;
        stopGame();
    }
}

void updateBanking(double ticks,float desiredAngle, GameObjectParams* params){
    // Rotate to maximum in 1 second:
    float currentEffect = params->effect.w;
    float calc = (ticks / 100) * spaceship_tilt_max_angle;
    
    if (desiredAngle < 0) {
        currentEffect -= calc;
        currentEffect = std::max(-spaceship_tilt_max_angle, currentEffect);
    } else if (desiredAngle > 0){
        currentEffect += calc;
        currentEffect = std::min(spaceship_tilt_max_angle, currentEffect);
    } else {
        if (currentEffect < 0){
            currentEffect += calc;
            currentEffect = std::min(0.0f, currentEffect);
        } else if (currentEffect > 0){
            currentEffect -= calc;
            currentEffect = std::max(0.0f, currentEffect);
        }
    }
    
    params->effect.w = currentEffect;
}

void SpaceBlasters::handleKeyboard(double ticks){
    if (gamestate == sb_GAMESTATE_PLAYING){
        float desiredAngle = 0;
        if (keyboard->keys[int('a')]){ // key: a
            spaceship->getParams()->rotation.w += (ticks / 20.0f);
            desiredAngle -= spaceship_tilt_max_angle;
        }
        if (keyboard->keys[int('d')]){ // key: d
            spaceship->getParams()->rotation.w -= (ticks / 20.0f);
            desiredAngle += spaceship_tilt_max_angle;
        }
        updateBanking(ticks, desiredAngle, spaceship->getParams());
        
        if (keyboard->keys[int('w')]){ // key: w
            spaceship->getParams()->movement.z = 1.5f;
        } else if (keyboard->keys[int('s')]) {
            spaceship->getParams()->movement.z = 0;
        } else {
            spaceship->getParams()->movement.z = 1;
        }
        
//        if (keyboard->keys[int('q')]){ // key: q
//            spaceship->getParams()->rotation.w -= (ticks / 20.0f);
//        }
//        if (keyboard->keys[int('e')]){ // key: e
//            spaceship->getParams()->rotation.w += (ticks / 20.0f);
//        }
        if (keyboard->keys[32]){ // spacebar
            keyboard->keys[32] = false; // Disable key
            shootProjectile();
        }
        
        if (keyboard->keys[int('p')]){ // key: p
            keyboard->keys[int('p')] = false; // Disable key
            spawner->Spawn();
        }
    } else {
        if (keyboard->keys[32]){ // spacebar
            keyboard->keys[32] = false; // Disable key
            gamestate = sb_GAMESTATE_PLAYING;
            restart();
        }
    }
//    if (keyboard->keys[int('c')]){
//        keyboard->keys[int('c')] = false;
//        followCam = !followCam;
//    }
}

void SpaceBlasters::updateCamera(){
    if (gamestate == sb_GAMESTATE_PLAYING){
        if (followCam){
            Vec3f pos = spaceship->getParams()->position;
            float radius = 10.0f;
            pos.x += (sin(AsRadian(spaceship->getParams()->rotation.w + 180)) * radius);
            pos.y += 3.0f;
            pos.z += (cos(AsRadian(spaceship->getParams()->rotation.w + 180)) * radius);
            camera->setPosition(pos);
            
            Vec3f lookAt = spaceship->getParams()->position;
            lookAt.y += 2.0f;
            camera->setLookAt(lookAt);
        } else {
            camera->setLookAt(Vec3f());
            Vec3f pos = Vec3f();
            float radius = 10.0f;
            pos.x += (sin(AsRadian(angle + 180)) * radius);
            pos.z += (cos(AsRadian(angle + 180)) * radius);
            pos.y += 0.0f;
            camera->setPosition(pos);
        }
    } else { // NOT PLAYING
        Vec3f pos = default_camera_position;
        float radius = 10.0f;
        pos.x += (sin(AsRadian(default_camera_rotation.w + 180)) * radius);
        pos.y += 3.0f;
        pos.z += (cos(AsRadian(default_camera_rotation.w + 180)) * radius);
        camera->setPosition(pos);
        
        Vec3f lookAt = default_camera_position;
        lookAt.y += 2.0f;
        camera->setLookAt(lookAt);
    }
}

void SpaceBlasters::spawnAsteroid(void){
    
}

void SpaceBlasters::shootProjectile(void){
    GameObjectParams* params = new GameObjectParams();
    params->active = true;
    params->movement = Matrix::Rotate(Vec3f(0.0f, 0.0f, 1.0f), spaceship->getParams()->rotation);
    params->rotation = spaceship->getParams()->rotation;
    
    // Initalize position. DO NOT use the matrix yet, we might need to translate.
    params->position = Vec3f(1.2f, 0.0f, 4.8f);
    // Translate accordingly based on the cannon.
    if (leftCannon) { params -> position.x *= -1; }
    leftCannon = !leftCannon;
    
    // Now we can rotate the position based on spaceship rotation
    params->position = Matrix::Rotate(params->position, spaceship->getParams()->effect);
    params->position = Matrix::Rotate(params->position, spaceship->getParams()->rotation);
    // And finally: Translate the vector to the currect position of the spacecraft.
    params->position += spaceship->getParams()->position;

    projectiles->Spawn(params);
}

void SpaceBlasters::collisionDetection(void){
    Vec3f distanceVect = Vec3f();
    for (const auto &asteroid : asteroids->objects){
        if (!asteroid->active) { continue; } // Skip inactive asteroids
        
        // Check collision with spacestation:
        distanceVect = asteroid->position - spacestation->getParams()->position;
        if (abs(distanceVect.length()) <= asteroids->collisionRadius + spacestation->collisionRadius){
            asteroid->active = false;
            health -= sb_ASTEROID_DAMAGE;
            std::cout << "BIEM: SpaceStation has been hit" << std::endl;
            std::cout << "HEALTH INFO: " << health << "hp left" << std::endl;
        }
        
        // Check collission with spaceship:
        distanceVect = asteroid->position - spacestation->getParams()->position;
        if (abs(distanceVect.length()) <= asteroids->collisionRadius + spacestation->collisionRadius){
            asteroid->active = false;
            health -= sb_SHIP_DAMAGE;
            std::cout << "WARNING: Your ship will be damaged if you do this!" << std::endl;
            std::cout << "HEALTH INFO: " << health << "hp left" << std::endl;
        }
        
        // Check collision with projectiles
        for (const auto &projectile : projectiles->objects){
            if (!projectile->active) { continue; } // Skip inactive projectiles
            
            distanceVect = asteroid->position - projectile->position;
            if (abs(distanceVect.length()) <= asteroids->collisionRadius + projectiles->collisionRadius){
                asteroid->active = false; // Remove it from field.
                projectile->active = false; // Also remove projectile as its "gone"
                continue;
            }
            
            // Check if we are shooting ourselves:
            distanceVect = projectile->position - spacestation->getParams()->position;
            if (abs(distanceVect.length()) <= projectiles->collisionRadius + spacestation->collisionRadius){
                projectile->active = false;
                health -= sb_PROJECTILE_DAMAGE;
                std::cout << "FRIENDLY FIRE: SpaceStation has been hit" << std::endl;
                std::cout << "HEALTH INFO: " << health << "hp left" << std::endl;
            }
        }
    }
}

void SpaceBlasters::drawHud(void){
    int const h = glutGet(GLUT_WINDOW_HEIGHT);
    //int const w = glutGet(GLUT_WINDOW_WIDTH);
    int x = 0;
    int y = 0;
    
    if (gamestate == sb_GAMESTATE_NOGAME || gamestate == sb_GAMESTATE_GAMEOVER) {
        y = h / 12;
        
        if (gamestate == sb_GAMESTATE_NOGAME) {
            Texthelper::ShowText("SpaceBlasters", 72, 350, y*9);
            Texthelper::ShowText("Press spacebar to start!", 48, 310, y*2);
        } else if (gamestate == sb_GAMESTATE_GAMEOVER) {
            Texthelper::ShowText("GAME OVER :(", 72, 350, y*9);
            Texthelper::ShowText("Press spacebar to start a new game", 48, 160, y*2);
        }
    }
    
    
    if (gamestate == sb_GAMESTATE_PAUSED || gamestate == sb_GAMESTATE_PLAYING)
    {
        std::ostringstream healthString;
        healthString << "SpaceStation health: " << health << "hp";
        const std::string tmp = healthString.str();
        y = h - 20;
        x = 10;
        
        Texthelper::ShowText(tmp, 14, x, y);
    }
}

// The call below will suspend OpenGL execution; we need anoter way...
//system("afplay /Users/jordysipkema/Downloads/SpaceBlasters/Assets/Audio/Biem.mp3");

