//
//  Texture.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 03/07/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define GL_SILENCE_DEPRECATION

#include "stb_image.h"
#include <iostream>


Texture::Texture(const string &filename)
{
    this->fileName = filename;
    int bpp2;
    
    stbi_set_flip_vertically_on_load(1);
    
    data = stbi_load(filename.c_str(), &width, &height, &bpp2, 4);
    if (!data)
        std::cout << stbi_failure_reason() << std::endl;
}

void Texture::Bind() {
    int window = glutGetWindow();
    if (textureIds.find(window) == textureIds.end())
    {
        printf("Building texture %s for window %i, data=%i\n", fileName.c_str(), window, (void*)data);
        GLuint textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width,
                     height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     data);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        textureIds[window] = textureId;
    }
    glBindTexture(GL_TEXTURE_2D, textureIds[window]);
}


Texture::~Texture()
{
    //TODO
    printf("Cleaning up %s\n", fileName.c_str());
    if(data)
        stbi_image_free(data);
    data = nullptr;
}


