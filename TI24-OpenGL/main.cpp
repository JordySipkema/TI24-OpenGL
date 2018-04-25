//
//  main.cpp
//  TI24-OpenGL
//
//  Created by Jordy Sipkema on 25-04-18.
//  Copyright © 2018 Jordy Sipkema. All rights reserved.
//

#include <GLUT/glut.h>
#include <iostream>
#include <math.h>

#include "Shape.hpp"
#include "Vec3f.hpp"

GLfloat rotation_speed = 10.0f;
GLfloat rotation = 0.0f;

GLfloat camera_rotation = 0.0f;
GLfloat camera_radius = 7.0f;
GLfloat camera_speed = 0.1f;

Vec3f center_cube_position = Vec3f();
Vec3f back_cube_color = Vec3f(1.0f, 0.0f, 0.0f);

bool orthogonal = false;
bool wireframe = false;

GLdouble lastFrametime = 0.0;

void reshape(GLsizei width, GLsizei height);

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            camera_rotation -= camera_speed;
            break;
        case 'd':
            camera_rotation += camera_speed;
            break;
        case ' ':
            orthogonal = !orthogonal;
            reshape(1200, 900);
            break;
        case 'w':
            wireframe = !wireframe;
            break;
        default:
            break;
    }
    
    if (key == 27)
        exit(0);
}

void keyboard_special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            center_cube_position.z -= 0.1f;
            break;
        case GLUT_KEY_DOWN:
            center_cube_position.z += 0.1f;
            break;
        case GLUT_KEY_LEFT:
            center_cube_position.x -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            center_cube_position.x += 0.1f;
            break;
        default:
            break;
    }
}

void mousemotion(int x, int y){
    GLfloat gradient = (GLfloat)x / 900.0f;
    back_cube_color.x = gradient;
}

/**
 GLUT idle function
 */
void idle() {
    double currentTime = glutGet(GLUT_ELAPSED_TIME);
    double deltaTime = currentTime - lastFrametime;
    lastFrametime = currentTime; // verschil in ms
    
    rotation += rotation_speed * deltaTime / 1000.0;
    
    glutPostRedisplay();
}

/**
 Handler for window re-size event. Called back when the window first appears and
 whenever the window is re-sized with its new width and height

 @param width The width of the window
 @param height The height of the window
 */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    
    if (orthogonal){
        glOrtho(-8.0f, 8.0f, -8.0f, 8.0f, 0.1f, 50.f);
    } else {
        gluPerspective(70.0f, aspect, 0.1f, 50.0f);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    
    glLoadIdentity();
    
    GLfloat camera_x = (GLfloat) sin(camera_rotation) * camera_radius;
    GLfloat camera_y = (GLfloat) camera_radius;
    GLfloat camera_z = (GLfloat) cos(camera_rotation) * camera_radius;
    gluLookAt(camera_x, camera_y, camera_z,  // Camera position
              0, 0, 0,                       // Look at
              0, 1, 0);                      // Top
    
    if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
    else { glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
    
    // Render a color-cube consisting of 6 quads with different colors
    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 0.0f);
    glRotatef(rotation, 1.0f, 0.0f, 0.0f);
    Shape::drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(center_cube_position.x, center_cube_position.y, center_cube_position.z);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    Shape::drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(5.0f, 0.0f, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    Shape::drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    Shape::drawCube(back_cube_color);
    glPopMatrix();
    
    glutSwapBuffers();
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int main(int argc, const char * argv[]) {
    glutInit(&argc, const_cast<char**>(argv));
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutCreateWindow("TI24-OpenGL - Week 1");
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mousemotion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_special);
    
    initGL();
    glutMainLoop();
    return 0;
}
