/* Copyright 2009 Sorin Stancu-Mara  */

#include "scene.h"
#include "node.h"
#include "link.h"

#include <string>
#include <cstdio>
#include <cstdlib>

using std::string;
using std::vector;

const vector<string> Scene::Tokenize(const string& line) {
    vector<string> result;
    int pos = 0;
    while (pos != string::npos ) {
        int next = line.find_first_of(" ", pos);
        if (next != string::npos) {
            result.push_back(line.substr(pos, next - pos));
            pos = next + 1;
        } else {
            result.push_back(line.substr(pos));
            pos = next;
        } 
    }
    return result;
}

void Scene::processLine(const string& buffer) {
    vector<string> tokens = Tokenize(buffer);
    if (tokens[0] == "n") registerNode(tokens);
    if (tokens[0] == "l") registerLink(tokens);
    // IGNORE
}

void Scene::registerNode(const vector<string>& line) {
    int id;
    for (int i = 0; i < line.size() - 1; ++i) {
        if (line[i] == "-s") id = atol(line[i + 1].c_str());
    }
    if (nodes_.find(id) != nodes_.end()) {
        printf("WARNING: two nodes with the same id: %d\n", id);
        printf("Subsequent definitions ignored!\n");
    } else {
        nodes_.insert(std::pair<int, Node*>(id, new Node(id)));
    }
}

void Scene::registerLink(const vector<string>& line) {
    int from_id = -1, to_id = -1;
    for (int i = 0; i < line.size() - 1; ++i) {
        if (line[i] == "-s") from_id = atol(line[i + 1].c_str());
        if (line[i] == "-d") to_id = atol(line[i + 1].c_str());
    }
    if (from_id == -1 || to_id == -1) {
        printf("ERROR: link definition is inconsistent\n");
    }
    if (nodes_.find(from_id) == nodes_.end() ||
        nodes_.find(to_id) == nodes_.end()) {
        printf("WARNING: Link between nodes that do not exist(%d, %d) "
               "ignored.\n", from_id, to_id);
    } else {
        links_.push_back(new Link(*nodes_[from_id], *nodes_[to_id])); 
    }
}

void Scene::LoadGraph(const string& fileName) {
    FILE* file = fopen(fileName.c_str(), "rt");
    if (file == NULL) {
        printf("ERROR: cannot open %s\n", fileName.c_str());
        return;
    }
    char buffer[2048];
    while (!feof(file)) {
        fgets(buffer, 2048, file);
        processLine(buffer);    
    }
    fclose(file);
}
