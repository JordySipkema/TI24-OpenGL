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

Keyboard::Keyboard() { }

void Keyboard::glutSpecial(int key, int x, int y)
{
    specKeys[key] = true;
}

void Keyboard::glutSpecialUp(int key, int x, int y)
{
    specKeys[key] = false;
}

void Keyboard::glutKeyboardUp(unsigned char key, int x, int y)
{
    keys[key] = false;
}

void Keyboard::glutKeyboard(unsigned char key, int x, int y)
{
    keys[key] = true;
}

void Keyboard::KeyboardIdle(double const &ticks){
    if(specKeys[GLUT_KEY_RIGHT])
    {
        
    }
    if(specKeys[GLUT_KEY_LEFT])
    {
        
    }
    if(specKeys[GLUT_KEY_UP]){

    }
    if(specKeys[GLUT_KEY_DOWN]){

    }
    if(keys[97]){ //a
    }
    if(keys[100]){ //d
    }
    if(keys[119]){ //w
    }
    if(keys[115]){ //s
    }
    if(keys[113]){ //q
    }
    if(keys[101]){ //e

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
