//
//  ObjModel.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 19/06/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//


#include "ObjModel.hpp"
#include <GLUT/glut.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "texture_loader.hpp"

/**
 * Replaces a substring in a string
 */

std::string replace(std::string str, std::string toReplace, std::string replacement)
{
    size_t index = 0;
    while (true)
    {
        index = str.find(toReplace, index);
        if (index == std::string::npos)
            break;
        str.replace(index, toReplace.length(), replacement);
        ++index;
    }
    return str;
}

/**
 * Splits a string into substrings, based on a separator
 */

static std::vector<std::string> split(std::string str, const std::string &separator)
{
    std::vector<std::string> ret;
    size_t index;
    while(true)
    {
        index = str.find(separator);
        if (index == std::string::npos)
            break;
        ret.push_back(str.substr(0, index));
        str = str.substr(index+1);
    }
    ret.push_back(str);
    return ret;
}

/**
 * Turns a string into lowercase
 */
inline std::string toLower(std::string data)
{
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

std::string& trimR(std::string& str)
{
    if (!str.size()) return str;
    // find the last whitespace chr, then delete from there to end.
    std::string::iterator iter = --str.end();
    while (isspace(*iter)) --iter;
    str.erase(++iter, str.end());
    return str;
}

std::string& trimL(std::string& str)
{
    if (!str.size()) return str;
    // find first non-whitespace, then delete from begin to there.
    std::string::iterator iter = str.begin();
    while (iter != str.end() && isspace(*iter)) ++iter;
    str.erase(str.begin(), iter);
    return str;
}

std::string& trim(std::string& str)
{
    return trimR(trimL(str));
}

/**
 * Cleans up a line for processing.
 */
static inline std::string cleanLine(std::string line)
{
    line = replace(line, "\t", " ");
    while (line.find("  ") != std::string::npos)
        line = replace(line, "  ", " ");
    if (line == "")
        return "";
    if (line[0] == ' ')
        line = line.substr(1);
    if (line == "")
        return "";
    if (line[line.length() - 1] == ' ')
        line = line.substr(0, line.length() - 1);
    return line;
}

/**
 * Loads an object model
 */
ObjModel::ObjModel(const std::string &fileName)
{
    std::cout << "Loading " << fileName << std::endl;
    std::string dirName = fileName;
    if(dirName.rfind("/") != std::string::npos)
        dirName = dirName.substr(0, dirName.rfind("/"));
    if(dirName.rfind("\\") != std::string::npos)
        dirName = dirName.substr(0, dirName.rfind("\\"));
    if(fileName == dirName)
        dirName = "";
    if(dirName == "/")
        dirName = "";
    
    
    std::ifstream pFile(fileName.c_str());
    
    if (!pFile.is_open())
    {
        std::cout << "Could not open file " << fileName << std::endl;
        return;
    }
    
    
    ObjGroup* currentGroup = new ObjGroup();
    currentGroup->materialIndex = -1;
    
    
    while(!pFile.eof())
    {
        std::string line;
        std::getline(pFile, line);
        line = cleanLine(line);
        if(line == "" || line[0] == '#') //skip empty or commented line
            continue;
        
        std::vector<std::string> params = split(line, " ");
        params[0] = toLower(params[0]);
        
        if(params[0] == "v")
            vertices.push_back(
                              Vec3f((float)atof(params[1].c_str()),
                                    (float)atof(params[2].c_str()),
                                    (float)atof(params[3].c_str())
                                    ));
        else if(params[0] == "vn")
            normals.push_back(
                              Vec3f((float)atof(params[1].c_str()),
                                    (float)atof(params[2].c_str()),
                                    (float)atof(params[3].c_str())
                                    ));
        else if(params[0] == "vt")
            texcoords.push_back(
                                Vec2f((float)atof(params[1].c_str()),
                                      (float)atof(params[2].c_str())
                                      ));
        else if(params[0] == "f")
        {
            for(size_t ii = 4; ii <= params.size(); ii++)
            {
                Face face;
                
                for(size_t i = ii-3; i < ii; i++)  //magische forlus om van quads triangles te maken ;)
                {
                    Vertex vertex;
                    std::vector<std::string> indices = split(params[i == (ii-3) ? 1 : i], "/");
                    if (indices.size() >= 1)  //er is een positie
                        vertex.position = atoi(indices[0].c_str()) - 1;
                    if(indices.size() == 2)    //alleen texture
                        vertex.texcoord = atoi(indices[1].c_str())-1;
                    if(indices.size() == 3)    //v/t/n of v//n
                    {
                        if( indices[1] != "")
                            vertex.texcoord = atoi(indices[1].c_str())-1;
                        vertex.normal = atoi(indices[2].c_str())-1;
                    }
                    face.vertices.push_back(vertex);
                }
                currentGroup->faces.push_back(face);
            }
        }
        else if(params[0] == "s")
        {//smoothing groups
        }
        else if(params[0] == "mtllib")
        {
            loadMaterialFile(dirName + "/" + params[1], dirName);
        }
        else if(params[0] == "usemtl")
        {
            if(currentGroup->faces.size() != 0)
                groups.push_back(currentGroup);
            currentGroup = new ObjGroup();
            currentGroup->materialIndex = -1;
            
            for(size_t i = 0; i < materials.size(); i++)
            {
                MaterialInfo* info = materials[i];
                if(info->name == params[1])
                {
                    currentGroup->materialIndex = (int)i;
                    break;
                }
            }
            if(currentGroup->materialIndex == -1)
                std::cout<<"Could not find material name "<<params[1]<<std::endl;
        }
    }
    groups.push_back(currentGroup);
}


ObjModel::~ObjModel(void)
{
}




void ObjModel::draw()
{
    for(ObjGroup *group: groups)
    {
        // If: hasColor and NOT hasTexture
        if ((materials[(*group).materialIndex])->hasColor && !(materials[(*group).materialIndex])->hasTexture) {
            glColor3f(
                      (materials[(*group).materialIndex])->color->getRed(),
                      (materials[(*group).materialIndex])->color->getGreen(),
                      (materials[(*group).materialIndex])->color->getBlue()
                      );
        }
        // Else if: NOT hasColor and hasTexture
        else if ((materials[(*group).materialIndex])->hasTexture)
        {
            glEnable(GL_TEXTURE_2D);
            (materials[(*group).materialIndex])->texture.loadTexture();
        }
        // Else if: NOT hasColor and NOT hasTexture
        else
        {
            glDisable(GL_TEXTURE_2D);
        }
        
        // Start drawing object:
        glBegin(GL_TRIANGLES);
        for (const Face &face: group->faces){
            for (const Vertex &v : face.vertices){
                glNormal3f(normals[v.normal].x, normals[v.normal].y, normals[v.normal].z);
                glTexCoord2f(texcoords[v.texcoord].x, texcoords[v.texcoord].y);
                glVertex3f(vertices[v.position].x, vertices[v.position].y, vertices[v.position].z);
            }
        }
        glEnd();
    }
    
    glDisable(GL_TEXTURE_2D);
}

void ObjModel::loadMaterialFile( const std::string &fileName, const std::string &dirName )
{
    std::string strippedFileName = fileName.c_str();
    
    if (!fileName.empty() && fileName[fileName.size() -1] == '\r')
        strippedFileName = fileName.substr(0, fileName.size()-1);
    
    std::cout << "Loading " << fileName << std::endl;
    
    std::ifstream pFile(strippedFileName.c_str());
    
    if (!pFile.is_open())
    {
        std::cout << "Could not open file " << fileName << std::endl;
        return;
    }
    
    MaterialInfo* currentMaterial = NULL;
    
    while(!pFile.eof())
    {
        std::string line;
        std::getline(pFile, line);
        line = cleanLine(line);
        if(line == "" || line[0] == '#')
            continue;
        
        std::vector<std::string> params = split(line, " ");
        params[0] = toLower(params[0]);
        
    if (params[0] == "newmtl")
    {
        if(currentMaterial != NULL)
        {
            materials.push_back(currentMaterial);
        }
        currentMaterial = new MaterialInfo();
        currentMaterial->name = params[1];
    //    currentMaterial->hasTexture = true;
    //    currentMaterial->texture = texture_loader(params[1]);
    //    currentMaterial->texture.initTexture();
    }
    else if(params[0] == "map_kd")
    {
        currentMaterial->hasTexture = true;
        std::string tex = trim(params[1]);
        if (tex.find("/"))
            tex = tex.substr(tex.rfind("/") + 1);
        if (tex.find("\\"))
            tex = tex.substr(tex.rfind("\\") + 1);
        currentMaterial->texture = texture_loader(dirName + "/" + tex);
        currentMaterial->texture.initTexture();
    }
    else if (params[0] == "kd"){
        currentMaterial->hasColor = true;
        currentMaterial->color = new ObjColor(atof(params[1].c_str()), atof(params[2].c_str()), atof(params[3].c_str()));
    }
    else if (params[0] == "ka")
    {//TODO, ambient color
    }
    else if (params[0] == "ks")
    {//TODO, specular color
    }
    else if (
             params[0] == "illum" ||
             params[0] == "map_bump" ||
             params[0] == "map_ke" ||
             params[0] == "map_ka" ||
             params[0] == "map_d" ||
             params[0] == "d" ||
             params[0] == "ke" ||
             params[0] == "ns" ||
             params[0] == "ni" ||
             params[0] == "td" ||
             params[0] == "tf" ||
             params[0] == "tr" ||
             false)
    {
        //these values are usually not used for rendering at this time, so ignore them
    }
    else
    std::cout<<"Didn't parse "<<params[0]<<" in material file"<<std::endl;
    }
    if(currentMaterial != NULL)
    materials.push_back(currentMaterial);

}
ObjModel::MaterialInfo::MaterialInfo()
{
    hasTexture = false;
}

ObjModel::ObjColor::ObjColor(float red, float green, float blue)
    : red(red), green(green), blue(blue)
{
}

void ObjModel::ObjColor::setColors(float red, float green, float blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

float ObjModel::ObjColor::getRed() {
    return this->red;
}
float ObjModel::ObjColor::getGreen() {
    return this->green;
}
float ObjModel::ObjColor::getBlue() {
    return this->blue;
}
