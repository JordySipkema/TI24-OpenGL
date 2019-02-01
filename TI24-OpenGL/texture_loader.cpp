//
//  texture_loader.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/12/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#define STB_IMAGE_IMPLEMENTATION
#include <unistd.h>
#include <GLUT/glut.h>
#include <string>
#include "stb_image.h"
#include <iostream>
using namespace std;

#include "texture_loader.hpp"

texture_loader::texture_loader(std::string fileName)
{
    texturePath = fileName;
}

texture_loader::texture_loader()
{
    texturePath = "";
}

void texture_loader::initTexture(void)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    stbi_set_flip_vertically_on_load(1);
    unsigned char* imgData = stbi_load(texturePath.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
    if(!imgData)
        printf("Error loading texture %s, %s\n", texturePath.c_str(), stbi_failure_reason());
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(imgData);
    
    std::cout << "Initialized texture " << texturePath << " with ID " << textureId << std::endl;
    
    glBindTexture(GL_TEXTURE_2D, textureId);
    glEnable(GL_TEXTURE_2D);
}

void texture_loader::loadTexture(void){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void texture_loader::getTexture(double x, double y)
{
    if (x>1||y>1||x<0||y<0) {
        printf("I can't use values above 1 or below 0!");
    }
    else glTexCoord2f(x,y);
}

void texture_loader::stashTexture(void)
{
    glDisable(GL_TEXTURE_2D);
}
