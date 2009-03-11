/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include <map>
#include <vector>
#include <string>

class Node;
class Link;

class Layout {
  public:
    Layout();

    void setNodes(const std::map<int, Node*>&);
    void setLinks(const std::vector<Link*>&);

    void recompute();
  private:
    void writeDotFile(const std::string& fileName) const;
    void readGraphVizOutput(const std::string& fileName);
    std::map<int, Node*> nodes_;
    std::map<std::pair<int, int>, Link*> links_;
};

#endif  // __LAYOUT_H__
