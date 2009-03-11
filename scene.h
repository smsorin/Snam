/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __SCENE_H__
#define __SCENE_H__

#include "vector3.h"
#include <vector>

class Node;
class Link;

class Scene {
  public:
    Scene(const std::string& fileName);
    const Vector3& getCamera() const;
    void setCamera(const Vector3&);

    void Tick(double delta);
    void Draw() const;
  private:
    Vector3 camera_;

    std::vector<Node*> nodes_;
    std::vector<Link*> links_;

    void LoadGraph(const std::string&);
    const std::vector<std::string> Tokenize(const std::string&);
    void registerNode(const std::vector<std::string>&);
    void registerLink(const std::vector<std::string>&);
    void processLine(const std::string&);
    Scene(const Scene&);
    Scene& operator=(const Scene&);
};

#endif  // __SCENE_H__
