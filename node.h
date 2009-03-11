/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include "vector3.h"

class Node {
  public:
    Node(int id);
    int getId() const;
    const std::string& getTag() const;
    void setTag(const std::string&);   
    const Vector3& getLocation() const;
    void setLocation(const Vector3&);

    void Draw() const;
  private:
    Node(const Node&);
    Node& operator=(const Node&);
    std::string tag_;
    Vector3 location_;
    const int id_;
};

#endif  // __NODE_H__
