/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __HUD_H__
#define __HUD_H__

#include <vector>

class Widget;
class Scene;

class Hud {
  public:
    Hud(const Scene& scene);
    ~Hud();
    void Draw() const;
  private:
    std::vector<Widget*> widgets_;
};

#endif  // __HUD_H__
