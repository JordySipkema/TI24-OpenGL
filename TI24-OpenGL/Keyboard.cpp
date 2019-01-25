//
//  Keyboard.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/12/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//



#define AsRadian(x) ((x)*(M_PI/180.0f))

#define _USE_MATH_DEFINES
#include <cmath>
#include <GLUT/glut.h>
#include "Keyboard.hpp"
#include "Camera.hpp"
bool specKeys[256];
bool keys[256];


void glutSpecial(int key, int x, int y)
{
    specKeys[key] = true;
}

void glutSpecialUp(int key, int x, int y)
{
    specKeys[key] = false;
}

void glutKeyboardUp(unsigned char key, int x, int y)
{
    keys[key] = false;
}

void glutKeyboard(unsigned char key, int x, int y)
{
    keys[key] = true;
}

void KeyboardIdle(double const &ticks, Camera camera){
    double factor = 0.1;
    camera.setEyeposHor(fmod(camera.getEyeposHor(), 360.0f));
    if(specKeys[GLUT_KEY_RIGHT])
    {
        camera.setEyeposHor(camera.getEyeposHor()+ticks/10);  //Rotate around center, right
    }
    if(specKeys[GLUT_KEY_LEFT])
    {
        camera.setEyeposHor(camera.getEyeposHor()-ticks/10);  //Rotate around center, left
    }
    if(specKeys[GLUT_KEY_UP]){
        camera.setCameraCenterY(camera.getCameraCenterY() + 0.1f); //Lookup
        if(camera.getCameraCenterY() > 10)
            camera.setCameraCenterY(10);
    }
    if(specKeys[GLUT_KEY_DOWN]){
        camera.setCameraCenterY(camera.getCameraCenterY() - 0.1f); //Lookdown
        if(camera.getCameraCenterY() < -10)
            camera.setCameraCenterY( -10);
    }
    if(keys[97]){ //a
        camera.setCameraCenterX(camera.getCameraCenterX() - factor * cos(AsRadian(camera.getEyeposHor() - 90)));       // Move left
        camera.setCameraCenterZ(camera.getCameraCenterZ() - factor * sin(AsRadian(camera.getEyeposHor() - 90)));
    }
    if(keys[100]){ //d
        camera.setCameraCenterX(camera.getCameraCenterX() - factor * cos(AsRadian(camera.getEyeposHor() + 90)));       // Move right
        camera.setCameraCenterZ(camera.getCameraCenterZ() - factor * sin(AsRadian(camera.getEyeposHor() + 90)));
    }
    if(keys[119]){ //w
        camera.setCameraCenterX(camera.getCameraCenterX() - factor * cos(AsRadian(camera.getEyeposHor())));       // Move forward
        camera.setCameraCenterZ(camera.getCameraCenterZ() - factor * sin(AsRadian(camera.getEyeposHor())));
    }
    if(keys[115]){ //s
        camera.setCameraCenterX(camera.getCameraCenterX() + factor * cos(AsRadian(camera.getEyeposHor())));       // Move backwards
        camera.setCameraCenterZ(camera.getCameraCenterZ() + factor * sin(AsRadian(camera.getEyeposHor())));
    }
    if(keys[113]){ //q
        camera.setEyeposVer(camera.getEyeposVer()+ticks/100); //Zoom out
    }
    if(keys[101]){ //e
        camera.setEyeposVer(camera.getEyeposVer()-ticks/100);
        if(camera.getEyeposVer() <= 0.5)
            camera.setEyeposVer(0.5);  //Zoom in
    }
    //    if(keys[6]){  //ctrl+f
    //        if(fullScreen){
    //            glutReshapeWindow(800, 600);            // Restore to window
    //            glutPositionWindow(0,0);
    //            fullScreen = !fullScreen;
    //        }
    //        else
    //        {
    //            glutFullScreen();                       // FullScreen glory
    //            fullScreen = !fullScreen;
    //        }
    //    }
    //    if(keys[112]){ //p
    //        rotating = !rotating;
    //    }
    if(keys[27]){ //ESCAPE
        exit(0);
        }
}
