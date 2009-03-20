/* Copyright 2009 Sorin Stancu-Mara */

#include "scene.h"
#include "node.h"
#include "link.h"
#include "mouse.h"
#include "layout.h"
#include "consts.h"
#include "keyboard.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>

using std::map;
using std::pair;

Scene::Scene(const std::string& fileName) {
    current_time_ = 0;
    end_time_ = 0;
    pause = false;
    time_coefficient_ = 1;
    LoadGraph(fileName);
    layout_ = new Layout();
    layout_->setNodes(nodes_);
    layout_->setLinks(links_);
    layout_->recompute();

    Vector3 min, max;
    min= max = nodes_.begin()->second->getLocation();
    for (map<int, Node*>::const_iterator it = nodes_.begin();
            it != nodes_.end(); ++it) {
       const Vector3& loc = it->second->getLocation(); 
       if (loc.x < min.x) min.x = loc.x;
       else if (loc.x > max.x) max.x = loc.x;
       if (loc.y < min.y) min.y = loc.y;
       else if (loc.y > max.y) max.y = loc.y;
       if (loc.z < min.z) min.z = loc.z;
       else if (loc.z > max.z) max.z = loc.z;
    }
    camera_ = (min + max) / 2;
    Vector3 area = max - min;
    if (area.x > area.y) camera_.z = area.x;
    else camera_.z = area.y;
}

Scene::~Scene() {
    delete layout_;
    layout_ = NULL;
    for (map<pair<int, int>, Link*>::iterator it = links_.begin();
            it != links_.end(); ++it) {
        delete it->second;
    }
    links_.clear();
    for (map<int, Node*>::iterator it = nodes_.begin();
            it != nodes_.end(); ++it) {
        delete it->second;
    }
    nodes_.clear();
}

const Vector3& Scene::getCamera() const { return camera_; }
void Scene::setCamera(const Vector3& newPos) { camera_ = newPos; }
const map<pair<int, int>, Link*>& Scene::getLinks() const { return links_; }
double Scene::getEndTime() const { return end_time_; }
double Scene::getTime() const { return current_time_; }

void Scene::printStatus() const {
    printf("%s current time: %lf speed: %lf \n",(pause? "paused" : "playing"),
           current_time_, time_coefficient_);
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

    // keyboard functions...
    static bool last_space = false;
    static bool last_double_speed = false;
    static bool last_half_speed = false;
    static bool last_faster = false;
    static bool last_slower = false;
    static bool last_reverse = false;
    if (Keyboard::key[' '] ^ last_space) {
        if (last_space) {
            pause = !pause;
            printStatus();
        }
        last_space = Keyboard::key[' '];
    }
    if (Keyboard::key['r'] || Keyboard::key['R']) time_coefficient_ = 1;
    if (Keyboard::key['}'] ^ last_double_speed) {
        time_coefficient_ *= last_double_speed ? 1: 2;
        last_double_speed = Keyboard::key['}'];
    }
    if (Keyboard::key['{'] ^ last_half_speed) {
        time_coefficient_ /= last_half_speed ? 1 : 2;
        last_half_speed = Keyboard::key['{'];
    }
    if (Keyboard::key[']'] ^ last_faster) {
        time_coefficient_ *= last_faster ? 1: 1.1;
        last_faster = Keyboard::key[']'];
    }
    if (Keyboard::key['['] ^ last_slower) {
        time_coefficient_ /= last_slower ? 1 : 1.1;
        last_slower = Keyboard::key['['];
    }
    if (Keyboard::key[GLUT_KEY_DOWN]) current_time_ -= 60.0;
    if (Keyboard::key[GLUT_KEY_UP]) current_time_ += 60.0;
    if (Keyboard::key[GLUT_KEY_LEFT]) current_time_ += 10.0;
    if (Keyboard::key[GLUT_KEY_RIGHT]) current_time_ -= 10.0;
    if (Keyboard::key['`'] ^ last_reverse) {
        time_coefficient_ *= last_reverse ? 1 : -1;
        last_reverse = Keyboard::key['`'];
    }
    
    if (!pause) {
        static double nextStatusUpdate = statusUpdateInterval;
        nextStatusUpdate -= delta;
        if (nextStatusUpdate < 0) {
            printStatus();
            nextStatusUpdate = statusUpdateInterval;            
        }
        current_time_ += delta * time_coefficient_;
        if (current_time_ > end_time_) {
            current_time_ = 0;
        } else if (current_time_ < 0) {
            current_time_ = end_time_;
        }
    }
}

void Scene::Draw() const {
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity();
    glTranslated(-camera_.x, -camera_.y, -camera_.z);
    for (map<pair<int, int>, Link*>::const_iterator it = links_.begin();
            it != links_.end(); ++it) {
        glPushMatrix();
        it->second->Draw(current_time_);
        glPopMatrix();
    }

    for (std::map<int, Node*>::const_iterator it = nodes_.begin();
         it != nodes_.end(); ++it) {
        glPushMatrix();
        (it->second)->Draw();
        glPopMatrix();
    }
}
