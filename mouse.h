/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "vector3.h"

class Mouse {
  public:
    static void Button(int button, int state, int x, int y);
    static void Motion(int x, int y);
    static Vector3 pos;
    static bool left, middle, right;
  private:
    Mouse();
    Mouse(const Mouse&);
    Mouse& operator=(const Mouse&);
};

#endif  // __MOUSE_H__
