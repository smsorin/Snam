/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __LINK_H__
#define __LINK_H__

#include <vector>
#include "vector3.h"

class Node;

class Link {
  public:
    Link(const Node& from, const Node& to);
    ~Link();
    const Node& getFrom() const;
    const Node& getTo() const;

    void Draw() const;
  private:          
    Link(const Link&);
    Link& operator=(const Link&);

    mutable std::vector<Vector3> controlPoints;
    mutable float *geometry;

    void setGeometryVertex(int pos, const Vector3& loc) const;
    void generateGeometry() const;

    const Node& from_;
    const Node& to_;
};

#endif  // __LINK_H__
