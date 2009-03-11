/* Copyright 2009 Sorin Stancu-Mara */

#include "node.h"
#include <GL/gl.h>

int Node::id_count_ = 0;

Node::Node() : id_(id_count_++) {
}

int Node::getId() const { return id_; }
const std::string& Node::getTag() const { return tag_; }
const Vector3& Node::getLocation() const { return location_; }

void Node::setTag(const std::string& new_tag) { tag_ = new_tag; }
void Node::setLocation(const Vector3& new_location) { location_ = new_location; }

void Node::Draw() const {
    glColor3d(1,0,0);
    glTranslated(location_.x, location_.y, location_.z);
    static float box[] = {-1, -1, 0,
                           1, -1, 0,
                           1,  1, 0,
                          -1,  1, 0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, box);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}
