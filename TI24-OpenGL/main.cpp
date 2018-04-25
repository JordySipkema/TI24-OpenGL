//
//  main.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 25-04-18.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include <GLUT/glut.h>
#include <iostream>

void keyboard(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

void idle() {
    glutPostRedisplay();
}

void display() {
    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glutSwapBuffers();
}

int main(int argc, const char * argv[]) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1200, 900);
    glutInit(&argc, const_cast<char**>(argv));
    glutCreateWindow("Hello World");
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}
