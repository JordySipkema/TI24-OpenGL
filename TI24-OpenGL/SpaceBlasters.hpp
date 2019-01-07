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
#include <GLUT/glut.h>
#include "glm/glm.hpp"

class SpaceBlasters
{
    
public:
    SpaceBlasters();
    
    void initGame(void);
    
    void draw(void);
    void update(void);
    
    void keyboard(unsigned char key, int x, int y);
};


#endif /* SpaceBlasters_hpp */
