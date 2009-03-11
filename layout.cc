/* Copyright 2009 Sorin Stancu-Mara */

#include "layout.h"
#include "node.h"
#include "link.h"
#include "vector3.h"
#include <cstring>
#include <cstdlib>

Layout::Layout() {}
void Layout::setNodes(const std::map<int,Node*>& nodes) {
    nodes_ = nodes;
}

void Layout::setLinks(const std::vector<Link*>& links) {
    links_.clear();
    for (unsigned int i = 0; i < links.size(); ++i) {
        links_.insert(std::pair<std::pair<int, int>, Link*>(
                    std::pair<int, int>(links[i]->getFrom().getId(),
                                        links[i]->getTo().getId()),
                    links[i]));
    }
}

void Layout::recompute() {
    printf("Rendering new layout...\n");
    char* aux = new char[100];
    static const char* name_template = "/tmp/snam.tmp.XXXXXX";
    strcpy(aux, name_template);
    mkstemp(aux);
    std::string fileName = aux;
    delete[] aux; aux = NULL;
    writeDotFile(fileName);
    char command [256];
    sprintf(command, "dot -Tplain -o%s %s",
            (fileName + ".out").c_str(),
            fileName.c_str());
    if (system(command)) {
        printf("Error: The layout engine didn't worked!\n");        
        return;
    }
    remove(fileName.c_str());
    readGraphVizOutput(fileName + ".out");
    remove((fileName+".out").c_str());
    for (std::map<std::pair<int, int>, Link*>::iterator it = links_.begin();
            it != links_.end(); ++it) {
        it->second->updateGeometry();
    }
    printf("DONE\n");
}

void Layout::readGraphVizOutput(const std::string& fileName) {
    FILE* f = fopen(fileName.c_str(), "rt");
    if (f == NULL) {
        printf("Error: Cannot open temporary output file!\n");
        return;
    }
    char buffer[65535];
    while (!feof(f)) {
        fgets(buffer, 65535, f);
        char *token = strtok(buffer, " ");
        if (strcmp(token, "graph") == 0) {
            // irelevant
        } else if (strcmp(token, "node") == 0) {
            int id = atol(strtok(NULL, " ")); 
            double x,y;
            sscanf(strtok(NULL, " "), "%lf", &x);
            sscanf(strtok(NULL, " "), "%lf", &y);
            nodes_[id]->setLocation(Vector3(x, y, 0.001));
        } else if (strcmp(token, "edge") == 0) {
            int from_id = atol(strtok(NULL, " "));
            int to_id = atol(strtok(NULL, " "));
            std::map<std::pair<int, int>, Link*>::iterator it =
                links_.find(std::pair<int, int>(from_id, to_id));
            if (it == links_.end()) { 
                printf("Error: Inexisting link description: %d -- %d\n", 
                       from_id, to_id);
                continue;
            }
            Link& link = *(it->second);
            link.clearControlPoints();
            int count = atol(strtok(NULL, " "));
            while (count--) {
                double x, y;
                sscanf(strtok(NULL, " "), "%lf", &x);
                sscanf(strtok(NULL, " "), "%lf", &y);
                link.addControlPoint(Vector3(x, y, 0.0));
            }
        } else if (strcmp(token, "stop\n") == 0) {
            break;
        } else {
            printf("Error: Unrecognized graph description line: %s\n", buffer);
        }
    }        
    fclose(f);
}

void Layout::writeDotFile(const std::string& fileName) const {
    FILE* f = fopen(fileName.c_str(), "wt"); 
    if (f == NULL) {
        printf("Error: Cannot open temporary file to write the graph!\n");
        return;
    }
    fprintf(f, "graph {\n");
    for (std::map<std::pair<int, int>, Link*>::const_iterator it = 
            links_.begin(); it != links_.end(); ++it) {
        fprintf(f, "  %d -- %d ;\n",
                it->first.first, it->first.second);
    }
    fprintf(f, "}\n");    
    fclose(f);
}