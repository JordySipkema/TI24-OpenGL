//
//  texture_loader.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/12/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef texture_loader_hpp
#define texture_loader_hpp

#include <stdio.h>
#include <string>

class texture_loader
{
private:
    int width, height, bpp, a;
    unsigned int textureId;
    std::string texturePath;
    
public:
    texture_loader(std::string);
    texture_loader();
    void getTexture(double, double);
    void loadTexture(void);
    void initTexture(void);
    void stashTexture(void);
};

#endif /* texture_loader_hpp */
