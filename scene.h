/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __SCENE_H__
#define __SCENE_H__

#include "vector3.h"
#include <vector>

class Node;
class Link;

class Scene {
  public:
    Scene();
    const Vector3& getCamera() const;
    void setCamera(const Vector3&);

    void Tick(double delta);
    void Draw() const;
  private:
    Vector3 camera_;

    std::vector<Node*> nodes_;
    std::vector<Link*> links_;
    Scene(const Scene&);
    Scene& operator=(const Scene&);
};

#endif  // __SCENE_H__
