/* Copyright 2009 Sorin Stancu-Mara */

#include "densitytimeline.h"
#include "consts.h"
#include "scene.h"
#include "message.h"
#include "link.h"
#include <map>
#include <cmath>
#include <cstdio>
#include "config.h"

using std::map;
using std::pair;
using std::multiset;

DensityTimeLine::DensityTimeLine(const Scene& scene) : scene_(scene) {
    int* buckets = new int[densityLineResolution];
    for (int  i = 0; i < densityLineResolution; i++) buckets[i] = 0;
    double bucketSize = scene.getEndTime() / glutGet(GLUT_WINDOW_WIDTH);
    for (map<pair<int, int>, Link*>::const_iterator it =
            scene.getLinks().begin(); it != scene.getLinks().end(); ++it) {
        const multiset<Message>& msgs = it->second->getForwardStream();
        index(msgs, buckets, bucketSize, *it->second);
        const multiset<Message>& msgs_reverse = it->second->getReverseStream();
        index(msgs_reverse, buckets, bucketSize, *it->second);
    }
    glEnable(GL_TEXTURE_2D);
    generateTexture(buckets);
    glDisable(GL_TEXTURE_2D);
    delete buckets;
}

void DensityTimeLine::Draw() const {
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0); 
    glVertex2d(0, height);
    glTexCoord2d(0.0, 1.0); 
    glVertex2d(width, height);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(width, height - densityLinehHeight);
    glTexCoord2d(1.0, 0.0); 
    glVertex2d(0.0, height - densityLinehHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    double timePos = scene_.getTime() / scene_.getEndTime();
    glColor4d(0.0, 0.0, 0.7, hudTransparency/255.0);
    glBegin(GL_QUADS);
    glVertex2d(timePos * width - 5, height);
    glVertex2d(timePos * width + 5, height);
    glVertex2d(timePos * width + 5, height - densityLinehHeight);
    glVertex2d(timePos * width - 5, height - densityLinehHeight); 
    glEnd(); 
    glDisable(GL_BLEND);
}

void DensityTimeLine::index(const multiset<Message>& msgs, int* buckets,
        double bucketSize, const Link& link) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    for (multiset<Message>::const_iterator it = msgs.begin(); 
            it != msgs.end(); ++it) {
        int pos = trunc(it->sendTime / bucketSize);
        double left = link.getFlyTime(*it);
        while (pos < width && left > 0) {
            buckets[pos++]++;
            left -= bucketSize;
        } 
    }
}

void DensityTimeLine::generateTexture(int* buckets) {
    int min, max;
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = width;
    unsigned char* data = new unsigned char[width * 
                                            height * 4];
    min = max = buckets[0];
    for (int i = 1; i < width; ++i) {
        if (buckets[i] > max) max = buckets[i];
        else if (buckets[i] < min) min = buckets[i];
    }
    for (int i = 0; i < width; ++i) {
        int level = height * (((double)buckets[i] - min) / (max - min));
        for (int j = 0; j < level; ++j) {
            data[(i*width+j) * 4 + 0] = densityLineFillColorRed;
            data[(i*width+j) * 4 + 1] = densityLineFillColorGreen;
            data[(i*width+j) * 4 + 2] = densityLineFillColorBlue;
            data[(i*width+j) * 4 + 3] = hudTransparency;
        }
        for (int j = level + 1; j < height; ++j) {
            data[(i*width+j) * 4 + 0] = 0;
            data[(i*width+j) * 4 + 1] = 0;
            data[(i*width+j) * 4 + 2] = 0;
            data[(i*width+j) * 4 + 3] = 0;  // Alpha
        }
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
                      width, height,
                      GL_RGBA, GL_UNSIGNED_BYTE, data);
    delete data;
}
