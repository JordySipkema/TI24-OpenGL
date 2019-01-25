//
//  Keyboard.hpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 17/12/2018.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <stdio.h>
#include <iostream>
#include "Camera.hpp"

void glutSpecial(int key, int x, int y);
void glutSpecialUp(int key, int x, int y);
void glutKeyboardUp(unsigned char key, int x, int y);
void glutKeyboard(unsigned char key, int x, int y);
void glutKeyboardUp(unsigned char, int, int);
void glutKeyboard(unsigned char, int, int);
void KeyboardIdle(double const &ticks, Camera);

#endif /* Keyboard_hpp */
