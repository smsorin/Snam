/* Copyright 2009 Sorin Stancu-Mara */

#include "keyboard.h"

bool Keyboard::key[256];
void Keyboard::Up(unsigned char key_, int x, int y) { key[key_] = false; }
void Keyboard::Down(unsigned char key_, int x, int y) { key[key_] = true; }

