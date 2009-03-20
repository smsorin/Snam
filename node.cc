/* Copyright 2009 Sorin Stancu-Mara */

#include "node.h"
#include "config.h"

Node::Node(int id) : id_(id), extent_(1.0, 1.0, 1.0) {
}

int Node::getId() const { return id_; }
const std::string& Node::getTag() const { return tag_; }
const Vector3& Node::getLocation() const { return location_; }
void Node::setExtent(const Vector3& extent) { extent_ = extent; }

void Node::setTag(const std::string& new_tag) { tag_ = new_tag; }
void Node::setLocation(const Vector3& new_location) { location_ = new_location; }

void Node::Draw() const {
    glColor3d(1,0,0);
    glTranslated(location_.x, location_.y, location_.z);
    glScaled(extent_.x, extent_.y, extent_.z);
    glScaled(0.1,0.1,1);
    glutSolidSphere(.5, 36, 5);
}
