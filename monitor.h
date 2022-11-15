#ifndef MONITOR_h
#define MONITOR_h

#include <Arduino.h>
#include "U8glib.h"

void monitor_display();
void draw_snake(int snake_arr[][2], int snake_len, int which_snake);
void draw_food(int x, int y);
void draw_score(int s1, int s2);

#endif
