//
//  SpaceBlasters.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//
#define AsRadian(x) ((x)*(M_PI/180.0f))
#define _USE_MATH_DEFINES

#define spaceship_initial_position Vec3f(0,0,-15)
#define spaceship_initial_rotation Vec4f(0,1,0,0)

#include <cmath>
#include <cstdlib>
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
    spawner->Start();
}

void SpaceBlasters::restart(void){
    health = sb_HEALTH;
    
    // Destroy phase: remove everything
    spaceship->Destroy();
    asteroids->Destroy();
    projectiles->Destroy();
    
    // Reset phase: reset everything for a new game
    spawner->Reset();
    GameObjectParams* params = new GameObjectParams(spaceship_initial_position, spaceship_initial_rotation);
    spaceship->Spawn(params);
    spawner->Start();
}

void SpaceBlasters::draw(void)
{
    updateCamera();
    //Reposition the environment around spaceship.
    environment->getParams()->position = spaceship->getParams()->position;
    
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
    if (health <= 0){ restart(); }
}

void SpaceBlasters::handleKeyboard(double ticks){
    if (keyboard->keys[int('a')]){ // key: a
        spaceship->getParams()->rotation.w += (ticks / 20.0f);
    }
    if (keyboard->keys[int('d')]){ // key: d
        spaceship->getParams()->rotation.w -= (ticks / 20.0f);
    }
    
    if (keyboard->keys[int('w')]){ // key: w
        spaceship->getParams()->movement.z = 1;
    } else {
        spaceship->getParams()->movement.z = 0;
    }
    
    if (keyboard->keys[int('q')]){ // key: q
        angle += (ticks / 20.0f);
    }
    if (keyboard->keys[int('e')]){ // key: e
        angle -= (ticks / 20.0f);
    }
    if (keyboard->keys[32]){ // spacebar
        keyboard->keys[32] = false; // Disable key
        shootProjectile();
    }
    
    if (keyboard->keys[int('p')]){ // key: p
        keyboard->keys[int('p')] = false; // Disable key
        
        GameObjectParams* params = new GameObjectParams();
        params->active = true;
        params->position = Vec3f();
        params->rotation = Vec4f(0.3f, 0.1f, 0.2f, 0.0f);
        asteroids->Spawn(params);
    }
    
    if (keyboard->keys[int('c')]){
        keyboard->keys[int('c')] = false;
        followCam = !followCam;
    }
}

void SpaceBlasters::updateCamera(){
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

// The call below will suspend OpenGL execution; we need anoter way...
//system("afplay /Users/jordysipkema/Downloads/SpaceBlasters/Assets/Audio/Biem.mp3");
