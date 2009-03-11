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
    if (id != nodes_.size()) {
        printf("PROBLEM: node id's don't respect the order in the file\n");
    }
    nodes_.push_back(new Node());
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
    links_.push_back(new Link(*nodes_[from_id], *nodes_[to_id])); 
}

void Scene::LoadGraph(const string& fileName) {
    FILE* file = fopen(fileName.c_str(), "rt");
    char buffer[2048];
    while (!feof(file)) {
        fgets(buffer, 2048, file);
        processLine(buffer);    
    }
    fclose(file);
}
