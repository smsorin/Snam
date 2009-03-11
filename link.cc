/* Copyright 2009 Sorin Stancu-Mara */

#include "link.h"
#include "node.h"
#include <GL/gl.h>

Link::Link(const Node& from, const Node& to)
    : from_(from), to_(to) {
    controlPoints.push_back(from_.getLocation() - Vector3(0.0,0.0,0.1));
    controlPoints.push_back(to_.getLocation() - Vector3(0.0, 0.0, 0.1));
}

Link::~Link() {
    if (geometry) {
        delete[] geometry;
        geometry = NULL;
    }
}

const Node& Link::getFrom() const { return from_; }
const Node& Link::getTo() const { return to_; }

void Link::Draw() const {
    if (!geometry) generateGeometry();
    glColor3d(0.0, 1.0, 0.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, geometry);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, controlPoints.size() * 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Link::generateGeometry() const {
    static const double link_width = 0.005;
    const int count = controlPoints.size();
    if (geometry) {
        delete[] geometry;
        geometry = NULL;
    }
    geometry = new float[3*2*count];
    static const Vector3 up(0,0,1);
    Vector3 dir = (controlPoints[1] - controlPoints[0]).Normalize();
    Vector3 left = dir.Cross(up).Normalize() * link_width; 
    setGeometryVertex(0, controlPoints[0] + left);
    setGeometryVertex(1, controlPoints[0] - left);
    for (int i = 1; i < count - 1; ++i) {
        dir = (controlPoints[i + 1] - controlPoints[i - 1]).Normalize();
        left = dir.Cross(up).Normalize() * link_width; 
        setGeometryVertex(i * 2, controlPoints[i] + left);
        setGeometryVertex(i * 2 +1, controlPoints[i] - left);
    }
    // last one
    dir = (controlPoints[count - 1] - controlPoints[count - 2]).Normalize();
    left = dir.Cross(up).Normalize() * link_width;
    setGeometryVertex(count *2 - 2, controlPoints[count - 1] + left);
    setGeometryVertex(count *2 - 1, controlPoints[count - 1] - left);
}

void Link::setGeometryVertex(int pos, const Vector3& loc) const {
    geometry[pos * 3 + 0] = loc.x;
    geometry[pos * 3 + 1] = loc.y;
    geometry[pos * 3 + 2] = loc.z;
}

void Link::clearControlPoints() {
    if (geometry) {
        delete[] geometry;
        geometry = NULL;
    }
    controlPoints.clear();
}

void Link::addControlPoint(const Vector3& newPoint) {
    controlPoints.push_back(newPoint);
}

void Link::updateGeometry() {
    if (geometry) {
        delete[] geometry;
        geometry = NULL;
    }
    for (int iteration = 0; iteration < 4; iteration++) {
        std::vector<Vector3> points;
        points.push_back(controlPoints[0]);
        for (unsigned int i = 1; i < controlPoints.size() - 1; ++i) {
            const Vector3& prev = controlPoints[i - 1];
            const Vector3& curent = controlPoints[i];
            const Vector3& next = controlPoints[i + 1];
            points.push_back(prev/3.0 + curent*(2.0/3.0));
            points.push_back(curent/3.0 + next*(2.0/3.0));
        }
        points.push_back(controlPoints[controlPoints.size() - 1]);
        controlPoints = points;
    }
    generateGeometry();
}
