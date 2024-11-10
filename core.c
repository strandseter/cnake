#include "core.h"

Config config() {
  Config config;

  config.size = 10;
  config.speed = 5;
  config.screenWidth = 400;
  config.screenHeight = 400;

  Directions directions;
  directions.right = 'R';
  directions.down = 'D';
  directions.left = 'L';
  directions.up = 'U';
  config.directions = directions;

  InitWindow(config.screenWidth, config.screenHeight, "CS50");

  SetTargetFPS(60);

  return config;
}

void change_direction(char *dir, Directions directions) {
  if (IsKeyPressed(KEY_RIGHT) && *dir != directions.left) {
    *dir = directions.right;
  }
  if (IsKeyPressed(KEY_DOWN) && *dir != directions.up) {
    *dir = directions.down;
  }
  if (IsKeyPressed(KEY_LEFT) && *dir != directions.right) {
    *dir = directions.left;
  }
  if (IsKeyPressed(KEY_UP) && *dir != directions.down) {
    *dir = directions.up;
  }
}

void move(char current_direction, Snake *head, Config cfg) {
  if (current_direction == cfg.directions.right) head->x += cfg.size;
  if (current_direction == cfg.directions.down) head->y += cfg.size;
  if (current_direction == cfg.directions.left) head->x -= cfg.size;
  if (current_direction == cfg.directions.up) head->y -= cfg.size;
}

bool game_over(Snake pos, Config cfg) {
  const int font_size = 40;
  const char* game_over = "GAME OVER!";
  const int text_width = MeasureText(game_over, font_size);

  const bool is_right_border = pos.x == cfg.screenWidth;
  const bool is_bottom_border = pos.y == cfg.screenHeight;
  const bool is_left_border = (pos.x + cfg.size) == 0;
  const bool is_top_border = (pos.y + cfg.size) == 0;

  const bool is_at_border = is_right_border || is_bottom_border || is_left_border || is_top_border;

  if (is_at_border) {
    DrawText(game_over, (cfg.screenWidth - text_width) / 2 , cfg.screenHeight / 2 - font_size / 2, font_size, RED);
  
    return true;
  }

  return false;
}

void draw_snake (Snake *snake, int len, Config cfg) {
  for (int i = 0; i < len; i++) {
    DrawRectangle(snake[i].x, snake[i].y, cfg.size, cfg.size, RED);
    DrawRectangleLines(snake[i].x, snake[i].y, cfg.size, cfg.size, BLACK);
  }
}






void debug_print(Snake pos, char direction) {
  printf("Current direction: %c\n", direction);
  printf("x: %d, y: %d\n", pos.x, pos.y);
}

void print_int(int num) {
  printf("%d\n", num);
}

void print_float(float num) {
  printf("%f\n", num);
}

void print_char(char c) {
  printf("%c\n", c);
}

void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
}