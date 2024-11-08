#ifndef CORE_H
#define CORE_H

#include "raylib.h"
#include "stdio.h"
#include "unistd.h"

typedef struct {
  char right;
  char down;
  char left;
  char up;
} Directions;

typedef struct {
    int size;
    int screenWidth;
    int screenHeight;
    Vector2 pos;
    Directions directions;
} Config;

Config config();
void debug_print(Vector2 pos, char direction);
void change_direction(char *direction, Directions directions);
void move(char current_direction, Vector2 *pos, Config cfg);
void draw_snake (Vector2 pos);
bool game_over(Vector2 pos, Config cfg);

#endif