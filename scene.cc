/* Copyright 2009 Sorin Stancu-Mara */

#include "scene.h"
#include "node.h"
#include "link.h"
#include "mouse.h"
#include "layout.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

Scene::Scene(const std::string& fileName) {
    LoadGraph(fileName);
    layout_ = new Layout();
    layout_->setNodes(nodes_);
    layout_->setLinks(links_);
    layout_->recompute();
}

Scene::~Scene() {
    delete layout_;
    layout_ = NULL;
    for (unsigned int i = 0; i < links_.size(); ++i) {
        delete links_[i];
    }
    links_.clear();
    for (std::map<int, Node*>::iterator it = nodes_.begin();
            it != nodes_.end(); ++it) {
        delete it->second;
    }
    nodes_.clear();
}

const Vector3& Scene::getCamera() const { return camera_; }

void Scene::setCamera(const Vector3& newPos) {
    camera_ = newPos;
}

void Scene::Tick(double delta) {
    static double last_mouse_pos_z = 0;
    camera_.z -= (Mouse::pos.z - last_mouse_pos_z) / 10.0;    
    last_mouse_pos_z = Mouse::pos.z;
    if (camera_.z < 1) camera_.z = 1;

    static bool last_left_state = false;
    if (Mouse::left) {        
        static Vector3 last_mouse_pos;
        if (!last_left_state) last_mouse_pos = Mouse::pos;
        Vector3 relative_drag_pixels = Mouse::pos - last_mouse_pos;
        const int window_width = glutGet(GLUT_WINDOW_WIDTH);
        const int window_height = glutGet(GLUT_WINDOW_HEIGHT);
        Vector3 relative_drag(relative_drag_pixels.x / window_width,
                              relative_drag_pixels.y / window_height, 0.0);
        static double coef = tan(M_PI / 6.0) * 2;
        const double scene_width = camera_.z * coef;
        const double scene_height = scene_width / 1.33;
        // the signs differ because of the coordinate systems are missalligned
        camera_.x -= scene_width * relative_drag.x;
        camera_.y += scene_height * relative_drag.y;
        last_mouse_pos = Mouse::pos;
    } 
    last_left_state = Mouse::left;
    // TODO:  animate stuff
}

void Scene::Draw() const {
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity();
    glTranslated(-camera_.x, -camera_.y, -camera_.z);
    for (unsigned int i = 0; i < links_.size(); ++i) {
        glPushMatrix();
        links_[i]->Draw();
        glPopMatrix();
    }

    for (std::map<int, Node*>::const_iterator it = nodes_.begin();
         it != nodes_.end(); ++it) {
        glPushMatrix();
        (it->second)->Draw();
        glPopMatrix();
    }
}
