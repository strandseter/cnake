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

Config cfg;
void initialize_config();

// Game state
bool game_over(Snake *snake, int lenr);
bool reset(Snake *snake, Food *food, int *len, char *current_direction, char *input_directionr);

// Food
Food spawn_food(Food food, Snake *snake, int len, char current_directionr) ;
bool is_no_food(Food food);
bool is_eating(Snake *snake, Food food);

// Movement
void track_input(char current_direction, char *input_direction, Directions directions);
void shift_body(Snake *snake, int len);
void move_head(char current_direction, Snake *headr);

// Draw
void draw_snake (Snake *body, int lenr);
void draw_game_over();
void draw_food(Food foodr);
void draw_start(char current_directionr);

// Debug
void debug_print(Snake pos, char direction);
void print_int(int num);
void print_char(char c);

#endif