/* Copyright 2009 Sorin Stancu-Mara */

#include "hud.h"
#include "scene.h"
#include "widget.h"
#include "densitytimeline.h"
#include "config.h"

Hud::Hud(const Scene& scene) {
    widgets_.push_back( new DensityTimeLine(scene) );
}

Hud::~Hud() {
    for (unsigned int i = 0; i < widgets_.size(); ++i) {
        delete widgets_[i];
        widgets_[i] = NULL;
    }
}

void Hud::Draw() const {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, width, 0, height);
    glScalef(1, -1, 1);
    glTranslatef(0, -height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    for (unsigned int i = 0; i < widgets_.size(); ++i) 
        widgets_[i]->Draw();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}
