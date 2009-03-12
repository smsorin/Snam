/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __DENSITYTIMELINE_H__
#define __DENSITYTIMELINE_H__

#include "widget.h"
#include "scene.h"
#include <set>
#include <GL/gl.h>

class Message;
class Link;

class DensityTimeLine : public Widget {
  public:
    DensityTimeLine(const Scene&);
    void Draw() const;
  private:
    void index(const std::multiset<Message>& msgs, int* buckets,
            double bucketSize, const Link& link);
    void generateTexture(int* buckets);
    GLuint texture;
    const Scene& scene_;
};

#endif  // __DENSITYTIMELINE_H__
