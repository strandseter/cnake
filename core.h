#ifndef CORE_H
#define CORE_H

#include "raylib.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "time.h"

typedef struct {
  int x;
  int y;
} Snake;

typedef struct {
  int x;
  int y;
} Food;

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
    Snake pos;
    Directions directions;
} Config;

Config config();
bool game_over(Snake *snake, int len, Config cfg);
bool reset(Snake *snake, Food *food, int *len, char *current_direction, char *input_direction, Config cfg);

// Food
Food spawn_food(Food food, Snake *snake, int len, char current_direction, Config cfg) ;
bool is_no_food(Food food);
bool is_eating(Snake *snake, Food food);

// Movement
void track_input(char current_direction, char *input_direction, Directions directions);
void shift_body(Snake *snake, int len);
void move_head(char current_direction, Snake *head, Config cfg);

// Draw
void draw_snake (Snake *body, int len, Config cfg);
void draw_game_over(Config cfg);
void draw_food(Food food, Config cfg);

// Debug
void debug_print(Snake pos, char direction);
void print_int(int num);
void print_char(char c);

#endif