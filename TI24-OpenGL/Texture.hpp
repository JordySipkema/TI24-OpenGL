//
//  Texture.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 03/07/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>

#include <string>
#include <GLUT/glut.h>
#include <map>

using std::string;

class Texture
{
private:
    std::string fileName;
    std::map<int, GLuint> textureIds;
    unsigned char* data = nullptr;
public:
    Texture(const string &filename);
    ~Texture();
    void Bind();
    
    int width;
    int height;
};

#endif /* Texture_hpp */
