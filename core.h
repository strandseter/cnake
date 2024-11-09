#ifndef CORE_H
#define CORE_H

#include "raylib.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

typedef struct {
  char right;
  char down;
  char left;
  char up;
} Directions;

typedef struct {
    int size;
    int speed;
    int screenWidth;
    int screenHeight;
    Vector2 pos;
    Directions directions;
} Config;

Config config();
bool game_over(Vector2 pos, Config cfg);

// Movement
void change_direction(char *dir, Directions directions);
void move(char current_direction, Vector2 *head, Config cfg);

// Draw
void draw_snake_head (Vector2 pos, Config cfg);
void draw_snake_body (Vector2 *body, int len, Config cfg);

// Debug
void debug_print(Vector2 pos, char direction);
void print_history(Vector2 *history, int size);

#endif