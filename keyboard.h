/* Copyright 2009 Sorin Stancu-Mara */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

class Keyboard {
  public:
    static void Up(unsigned char key, int x, int y);
    static void Down(unsigned char key, int x, int y);
      
    static bool key[256];
  private:
    Keyboard();
};

#endif  // __KEYBOARD_H__
