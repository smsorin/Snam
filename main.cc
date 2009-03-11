/* Copyright 2009 Sorin Stancu-Mara */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <sys/time.h>

#include "scene.h"
#include "mouse.h"
#include <cstdio>
#include <string>
#include <cstring>

Scene* scene;
std::string sceneName;

void Init() {
    printf("Initializing...");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.33, 0.001, 1000);
    glMatrixMode(GL_MODELVIEW);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    printf("DONE\n");
}

void Idle() {
    static timeval last_time;
    timeval current_time;
    double time_diff;
    gettimeofday(&current_time, NULL);
    if (last_time.tv_usec == 0 && last_time.tv_sec == 0) time_diff = 0;
    else time_diff = (current_time.tv_sec - last_time.tv_sec) +
            ((double)current_time.tv_usec - last_time.tv_usec) / 1000000.0;
    last_time = current_time;
    if (scene != NULL) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->Tick(time_diff);
        scene->Draw();
        glutSwapBuffers();
    }    
}

int main(int argc, char **argv) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "--file")) {
            sceneName = argv[i + 1];
        }
    }  
    if (sceneName == "") {
        printf("Error: Missing --file Parameter\n");
        return -1;
    } 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Sorin's Network Animator");
//    glutFullscreen();
//    glutKeyboradFunc(Keyboard::Down);
//    glutKeyboradUpFunc(Keyboard::Up);
    glutMouseFunc(Mouse::Button);
    glutMotionFunc(Mouse::Motion);
    glutPassiveMotionFunc(Mouse::Motion);
    glutIdleFunc(Idle);
    glutDisplayFunc(Idle);
    Init();

    scene = new Scene(sceneName);    
    glutMainLoop();
    delete scene;
    return 0;
}
