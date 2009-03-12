/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __WIDGET_H__
#define __WIDGET_H__

class Widget {
  public:
    virtual ~Widget();
    virtual void Draw() const = 0;
};

#endif  // __WIDGET_H__
