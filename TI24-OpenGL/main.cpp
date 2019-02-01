//
//  main.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 25-04-18.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//
#define GL_SILENCE_DEPRECATION // Silence the OpenGL/Glut deprecation warnings.

#define AsRadian(x) ((x)*(M_PI/180.0f))
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <vector>

#include <GLUT/glut.h>
#include <iostream>
#include "SpaceBlasters.hpp"
#include "Keyboard.hpp"
#include "Camera.hpp"
#include "texture_loader.hpp"
#include "ObjModel.hpp"
#include "Vec.hpp"

#define NO_ROTATION     0
#define X_AXIS_ROTATION 1
#define Y_AXIS_ROTATION 2
#define Z_AXIS_ROTATION 3
#define FOLLOW_CAM      4
#define NO_TEXTURE      5
#define DEFAULT_TEXTURE 6

static float framesPerSecond    = 0.0f;       // This will store our fps
static float lastTime   = 0.0f;       // This will hold the time from the last frame

float rotation = 0.0f;
int lastTick = 0;

std::string terrain = "terrain.png";
texture_loader texture1(terrain);

std::vector<std::pair<int, ObjModel*> > models;
int currentModel = 0;

void gfxDrawCube(float, float, float, float, int, int);
void Display(void);
void Reshape(GLint, GLint);
void InitGraphics(void);
void MouseButton(int, int, int, int);
void MouseMotion(int, int);
void glutSpecial(int, int, int);
void glutSpecialUp(int, int, int);
void onDisplay();
void rSleep(int);
void IdleFunc(void);
Keyboard* keyboard = new Keyboard();
Camera* camera = new Camera();
SpaceBlasters* game = new SpaceBlasters(camera, keyboard);

void gfxDrawCube(float posX, float posY, float posZ, float size, int angle, int texture){
    glPushMatrix();
    glTranslatef((size/2)+posX,(size/2)+posY,(size/2)+posZ);
    switch(angle){
        case 1:
            glRotatef(rotation,1,0,0);
            break;
        case 2:
            glRotatef(rotation,0,1,0);
            break;
        case 3:
            glRotatef(rotation,0,0,1);
            break;
        case 4:
            glRotatef(-camera->getEyeposHor(),0,1,0);
            break;
    }
    glTranslatef(-(size/2)-posX,-(size/2)-posY,-(size/2)-posZ);
    if (texture == DEFAULT_TEXTURE) {
        texture1.loadTexture();
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glNormal3f(0.0f,0.0f,-1.0f);
        texture1.getTexture(0.248, 0.062);
        glVertex3f(posX,posY,posZ);
        texture1.getTexture(0.248, 0.000);
        glVertex3f(posX,posY+size,posZ);
        texture1.getTexture(0.186, 0.000);
        glVertex3f(posX+size,posY+size,posZ);
        texture1.getTexture(0.186, 0.062);
        glVertex3f(posX+size,posY,posZ);
        
        glNormal3f(0.0f,0.0f,1.0f);
        texture1.getTexture(0.186, 0.062);
        glVertex3f(posX,posY,posZ+size);
        texture1.getTexture(0.186, 0.000);
        glVertex3f(posX,posY+size,posZ+size);
        texture1.getTexture(0.248, 0.000);
        glVertex3f(posX+size,posY+size,posZ+size);
        texture1.getTexture(0.248, 0.062);
        glVertex3f(posX+size,posY,posZ+size);
        
        glNormal3f(-1.0f,0.0f,0.0f);
        texture1.getTexture(0.186, 0.062);
        glVertex3f(posX,posY,posZ);
        texture1.getTexture(0.248, 0.062);
        glVertex3f(posX,posY,posZ+size);
        texture1.getTexture(0.248, 0.000);
        glVertex3f(posX,posY+size,posZ+size);
        texture1.getTexture(0.186, 0.000);
        glVertex3f(posX,posY+size,posZ);
        
        glNormal3f(1.0f,0.0f,0.0f);
        texture1.getTexture(0.248, 0.062);
        glVertex3f(posX+size,posY,posZ);
        texture1.getTexture(0.186, 0.062);
        glVertex3f(posX+size,posY,posZ+size);
        texture1.getTexture(0.186, 0.000);
        glVertex3f(posX+size,posY+size,posZ+size);
        texture1.getTexture(0.248, 0.000);
        glVertex3f(posX+size,posY+size,posZ);
        
        glNormal3f(0.0f,-1.0f,0.0f);
        texture1.getTexture(0.124, 0.062);
        glVertex3f(posX,posY,posZ);
        texture1.getTexture(0.124, 0.000);
        glVertex3f(posX,posY,posZ+size);
        texture1.getTexture(0.186, 0.000);
        glVertex3f(posX+size,posY,posZ+size);
        texture1.getTexture(0.186, 0.062);
        glVertex3f(posX+size,posY,posZ);
        
        glNormal3f(0.0f,1.0f,0.0f);
        texture1.getTexture(0.000, 0.062);
        glVertex3f(posX,posY+size,posZ);
        texture1.getTexture(0.062, 0.062);
        glVertex3f(posX,posY+size,posZ+size);
        texture1.getTexture(0.062, 0.000);
        glVertex3f(posX+size,posY+size,posZ+size);
        texture1.getTexture(0.000, 0.000);
        glVertex3f(posX+size,posY+size,posZ);
        glEnd();
        texture1.stashTexture();
        
    }
    else if(texture == NO_TEXTURE)
    {
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex3f(posX,posY,posZ);
        glVertex3f(posX,posY+size,posZ);
        glVertex3f(posX+size,posY+size,posZ);
        glVertex3f(posX+size,posY,posZ);
        
        glColor3f(1, 1, 1);
        glVertex3f(posX,posY,posZ+size);
        glVertex3f(posX,posY+size,posZ+size);
        glVertex3f(posX+size,posY+size,posZ+size);
        glVertex3f(posX+size,posY,posZ+size);
        
        glColor3f(1,0.90,1);
        glVertex3f(posX,posY,posZ);
        glVertex3f(posX,posY,posZ+size);
        glVertex3f(posX,posY+size,posZ+size);
        glVertex3f(posX,posY+size,posZ);
        
        glColor3f(1,0.85,1);
        glVertex3f(posX+size,posY,posZ);
        glVertex3f(posX+size,posY,posZ+size);
        glVertex3f(posX+size,posY+size,posZ+size);
        glVertex3f(posX+size,posY+size,posZ);
        
        glColor3f(1,0.80,1);
        glVertex3f(posX,posY,posZ);
        glVertex3f(posX,posY,posZ+size);
        glVertex3f(posX+size,posY,posZ+size);
        glVertex3f(posX+size,posY,posZ);
        
        glColor3f(1,0.70,1);
        glVertex3f(posX,posY+size,posZ);
        glVertex3f(posX,posY+size,posZ+size);
        glVertex3f(posX+size,posY+size,posZ+size);
        glVertex3f(posX+size,posY+size,posZ);
        glEnd();
    }
    
    glPopMatrix();
}

void fpsCounter(void){
    float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.001f;
    ++framesPerSecond;
    if( currentTime - lastTime > 1.0f )
    {
        lastTime = currentTime;
        if(1 == 1) fprintf(stderr, "\nCurrent Frames Per Second: %d\n\n", (int)framesPerSecond);
        framesPerSecond = 0;
    }
}

void Display(void)
{
    glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
}

void InitGraphics(void)
{
    glEnable(GL_DEPTH_TEST);
}

void MouseButton(int button, int state, int x, int y)
{
    
}

void MouseMotion(int x, int y)
{
    
}



void onDisplay(){
    fpsCounter();
    int const w = glutGet(GLUT_WINDOW_WIDTH);
    int const h = glutGet(GLUT_WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
              //Eye
              camera->getPosition().x,
              camera->getPosition().y,
              camera->getPosition().z,
              //Center
              camera->getLookAt().x,
              camera->getLookAt().y,
              camera->getLookAt().z,
              //Up
              0,1,0
              );

    game->draw();

    glutSwapBuffers();
}

void Sleep(int millisec){
   usleep(millisec);
}

void IdleFunc(void)
{
    int timeNow = glutGet(GLUT_ELAPSED_TIME);
    double ticks = (timeNow - lastTick);
    lastTick = timeNow;
    rotation += ticks/10;
    keyboard->KeyboardIdle(ticks);
    
    
    game->update(ticks);
    
    Sleep(ticks/10);
    glutPostRedisplay();
}

void glutKeyboard(unsigned char key, int x, int y){
    keyboard->glutKeyboard(key, x, y);
}
void glutKeyboardUp(unsigned char key, int x, int y){
    keyboard->glutKeyboardUp(key, x, y);
}
void glutSpecialUp(int key, int x, int y){
    keyboard->glutSpecialUp(key, x, y);
}
void glutSpecial(int key, int x, int y){
    keyboard->glutSpecial(key, x, y);
}

int main(int argc, char * argv[])
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutInit(&argc, argv);
    glutCreateWindow("Spaceblasters");
    printf("Programme started!\n");
    InitGraphics();
    //Models 'borrowed' from Johan
    //models.push_back(pair<int, ObjModel*>(75, new ObjModel("models/car/honda_jazz.obj")));    //Too large!
    //models.push_back(std::pair<int, ObjModel*>(1, new ObjModel("PrimroseP.mtl")));
    //models.push_back(std::pair<int, ObjModel*>(12, new ObjModel("spacecraft/spacecraft.obj")));
    //models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/cube/cube-textures.obj")));
    //models.push_back(pair<int, ObjModel*>(35, new ObjModel("models/ship/shipA_OBJ.obj")));    //Too large!
    //models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/normalstuff/normaltest2.obj")));
    glutDisplayFunc (onDisplay);
    glutReshapeFunc (Reshape);
    glutKeyboardFunc (glutKeyboard);
    glutKeyboardUpFunc(glutKeyboardUp);
    glutMouseFunc (MouseButton);
    glutMotionFunc (MouseMotion);
    glutSpecialFunc (glutSpecial);
    glutSpecialUpFunc (glutSpecialUp);
    glutIdleFunc (IdleFunc);
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    //glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
//    float FogCol[3]={1.0f,1.0f,1.0f};
//    glFogfv(GL_FOG_COLOR,FogCol);
//    glFogi(GL_FOG_MODE, GL_LINEAR);
//    glFogf(GL_FOG_START, 7.f);
//    glFogf(GL_FOG_END, 15.f);
    texture1.initTexture();
    game->initGame();
    glutMainLoop();
}

