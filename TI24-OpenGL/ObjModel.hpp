//
//  ObjModel.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 19/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef ObjModel_h
#define ObjModel_h

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <GLUT/glut.h>
#include "Vec.hpp"
#include "texture_loader.hpp"
//#include "Texture.hpp"

class ObjModel
{
private:
    class Vertex
    {
    public:
        int position;
        int normal;
        int texcoord;
    };
    
    class ObjColor {
    private:
        float red;
        float green;
        float blue;
    public:
        ObjColor(float red, float green, float blue);
        void setColors(float red, float green, float blue);
        float getRed();
        float getGreen();
        float getBlue();
    };
    
    class Face
    {
    public:
        std::list<Vertex> vertices;
    };
    
    
    class MaterialInfo
    {
    public:
        MaterialInfo();
        std::string name;
        texture_loader texture;
        bool hasTexture;
        ObjColor* color;
        bool hasColor;
    };
    
    class ObjGroup
    {
    public:
        std::string name;
        int materialIndex;
        std::list<Face> faces;
    };
    
    
    std::vector<Vec3f>  vertices;
    std::vector<Vec3f>  normals;
    std::vector<Vec2f>  texcoords;
    std::vector<ObjGroup*> groups;
    std::vector<MaterialInfo*> materials;
    
    void loadMaterialFile(const std::string &fileName, const std::string &dirName);
public:
    ObjModel(const std::string &filename);
    ~ObjModel(void);
    
    void draw();
};

#endif /* ObjModel_h */
