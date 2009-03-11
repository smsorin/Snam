/* Copyright 2009 Sorin Stancu-Mara  */

#include "scene.h"
#include "node.h"
#include "link.h"

#include <string>
#include <cstdio>
#include <cstdlib>

using std::string;
using std::vector;
using std::map;
using std::pair;

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
    if (tokens[0] == "h") registerPacket(tokens);
    // IGNORE
}

void Scene::registerPacket(const vector<string>& line) {
    int from_id = -1, to_id = -1;
    double sent_time = -1;
    int size = -1;
    for (int i = 0; i < line.size() - 1; ++i) {
        if (line[i] == "-s") from_id = atol(line[++i].c_str());
        else if (line[i] == "-d") to_id = atol(line[++i].c_str());
        else if (line[i] == "-t") sscanf(line[++i].c_str(), "%lf", &sent_time);
        else if (line[i] == "-e") size = atol(line[++i].c_str());
    }
    if (from_id == -1 || to_id == -1 || size == -1 || sent_time == -1) {
        printf("ERROR: packet definition is inconsistent\n");
    }
    map<pair<int, int>, Link*>::iterator it;
    it = links_.find(pair<int, int>(from_id, to_id));
    if (it != links_.end()) {
        it->second->addForwardMessage(Message(sent_time, size));        
    } else {
        it = links_.find(pair<int, int>(to_id, from_id));
        if (it == links_.end()) {
            printf("ERROR: packet defined but the link does not exist!\n");
        } else {
            it->second->addReverseMessage(Message(sent_time, size));
        }
    }
    if (end_time_ < sent_time + it->second->getDelay()) {
        end_time_ = sent_time + it->second->getDelay();
        printf("%lf\n", end_time_);
    }
}

void Scene::registerNode(const vector<string>& line) {
    int id;
    for (int i = 0; i < line.size() - 1; ++i) {
        if (line[i] == "-s") id = atol(line[++i].c_str());
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
    int capacity = -1;
    double delay = -1;
    for (int i = 0; i < line.size() - 1; ++i) {
        if (line[i] == "-s") from_id = atol(line[++i].c_str());
        else if (line[i] == "-d") to_id = atol(line[++i].c_str());
        else if (line[i] == "-r") capacity = atol(line[++i].c_str());
        else if (line[i] == "-D") sscanf(line[++i].c_str(), "%lf", &delay);
    }
    if (from_id == -1 || to_id == -1 || capacity == -1 || delay == -1) {
        printf("ERROR: link definition is inconsistent\n");
    }
    if (nodes_.find(from_id) == nodes_.end() ||
        nodes_.find(to_id) == nodes_.end()) {
        printf("WARNING: Link between nodes that do not exist(%d, %d) "
               "ignored.\n", from_id, to_id);
    } else {
        if (links_.find(pair<int, int>(from_id, to_id)) != links_.end() ||
            links_.find(pair<int, int>(to_id, from_id)) != links_.end()) {
            printf("WARNING: Link between %d and %d already defined!\n",
                    from_id, to_id);
        } else {
            Link* link = new Link(*nodes_[from_id], *nodes_[to_id]);
            link->setCapacity(capacity);
            link->setDelay(delay);
            links_.insert(pair<pair<int, int>, Link*>(
                        pair<int, int>(from_id, to_id),
                        link)); 
        }
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
