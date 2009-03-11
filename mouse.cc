/* Copyright 2009 Sorin Stancu-Mara */

#include "mouse.h"
#include <GL/glut.h>
#include <cstdio>

#ifndef GLUT_WHEEL_UP
    #define GLUT_WHEEL_UP   3
    #define GLUT_WHEEL_DOWN 4
#endif

Vector3 Mouse::pos(0,0,0);
bool Mouse::left = false, Mouse::middle = false, Mouse::right = false;

void Mouse::Button (int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            left = state == GLUT_DOWN;
            break;
        case GLUT_MIDDLE_BUTTON:
            middle = state == GLUT_DOWN;
            break;
        case GLUT_RIGHT_BUTTON:
            right = state == GLUT_DOWN;
            break;
        case GLUT_WHEEL_UP:
            pos.z += 1;
            break;
        case GLUT_WHEEL_DOWN:
            pos.z -= 1;
            break;
        default:
            printf("Unknown mouse button activity: %d\n", button);
            break;
    }
    pos.x = x;
    pos.y = y;
}

void Mouse::Motion(int x, int y) {
    pos.x = x;
    pos.y = y;
}
