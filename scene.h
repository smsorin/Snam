/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __SCENE_H__
#define __SCENE_H__

#include "vector3.h"
#include <vector>
#include <map>

class Node;
class Link;
class Layout;

class Scene {
  public:
    Scene(const std::string& fileName);
    ~Scene();
    const Vector3& getCamera() const;
    void setCamera(const Vector3&);
    const std::map<std::pair<int, int>, Link*>& getLinks() const;

    void Tick(double delta);
    void Draw() const;

    void printStatus() const;    
    double getEndTime() const;
    double getTime() const;
  private:
    Vector3 camera_;
    double current_time_;
    double end_time_;
    double time_coefficient_;
    bool pause;

    Layout* layout_;
    std::map<int, Node*> nodes_;
    std::map<std::pair<int, int>, Link*> links_;

    void LoadGraph(const std::string&);
    const std::vector<std::string> Tokenize(const std::string&);
    void registerNode(const std::vector<std::string>&);
    void registerLink(const std::vector<std::string>&);
    void registerPacket(const std::vector<std::string>&);
    void processLine(const std::string&);
   
    Scene(const Scene&);
    Scene& operator=(const Scene&);
};

#endif  // __SCENE_H__
