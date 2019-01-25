//
//  SpaceBlasters.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 18/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include "SpaceBlasters.hpp"
#include "GameObjects/SpaceShip.hpp"


SpaceBlasters::SpaceBlasters() { }

void SpaceBlasters::initGame(void) {
    spaceship = new SpaceShip(Vec3f(0, 10, 0), Vec4f(0,1,0,0), 7);
}

void SpaceBlasters::draw(void)
{
    spaceship->Draw();
    // foreach element: draw it
    // first: enviroment
    // then: models, etc..
}

void SpaceBlasters::update(int ticks)
{
    spaceship->Update(ticks);
}

void SpaceBlasters::keyboard(unsigned char key, int x, int y)
{
}
