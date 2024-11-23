#include "core.h"

Config config() {
  Config config;

  config.size = 10;
  config.speed = 3;
  config.screenWidth = 400;
  config.screenHeight = 400;

  Directions directions;
  directions.right = 'R';
  directions.down = 'D';
  directions.left = 'L';
  directions.up = 'U';
  config.directions = directions;

  InitWindow(config.screenWidth, config.screenHeight, "SNAKE50");

  SetTargetFPS(60);

  return config;
}

void track_input(char current_direction, char *input_direction, Directions directions) {
  if (IsKeyPressed(KEY_RIGHT) && current_direction != directions.left) {
    *input_direction = directions.right;
  }
  if (IsKeyPressed(KEY_DOWN) && current_direction != directions.up) {
    *input_direction = directions.down;
  }
  if (IsKeyPressed(KEY_LEFT) && current_direction != directions.right) {
    *input_direction = directions.left;
  }
  if (IsKeyPressed(KEY_UP) && current_direction != directions.down) {
    *input_direction = directions.up;
  }
}

void shift_body(Snake *snake, int len) {
  for (int i = len - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
}

void move_head(char current_direction, Snake *head, Config cfg) {
  if (current_direction == cfg.directions.right) head->x += cfg.size;
  if (current_direction == cfg.directions.down) head->y += cfg.size;
  if (current_direction == cfg.directions.left) head->x -= cfg.size;
  if (current_direction == cfg.directions.up) head->y -= cfg.size;
}

Food spawn_food(Food food, Snake *snake, int len, char current_direction, Config cfg) {
  if (current_direction == '_') {
    return food;
  }

  int x = (rand() % (cfg.screenWidth / cfg.size)) * cfg.size;
  int y = (rand() % (cfg.screenHeight / cfg.size)) * cfg.size;

  for (int i = 0; i < len; i++) {
    while (snake[i].x == x && snake[i].y == y) {
      x = (rand() % (cfg.screenWidth / cfg.size)) * cfg.size;
      y = (rand() % (cfg.screenHeight / cfg.size)) * cfg.size;
    }
  }

  // TODO: Check if snake covers whole screen
  int max = 

  food.x = x;
  food.y = y;

  return food;
}

bool is_no_food(Food food) {
  return food.x == -1 && food.y == -1;
}

bool is_eating(Snake *snake, Food food) {
  return snake[0].x == food.x && snake[0].y == food.y;
}

bool game_over(Snake *snake, int len, Config cfg) {
  Snake head = snake[0];

  const bool is_right_border = head.x == cfg.screenWidth;
  const bool is_bottom_border = head.y == cfg.screenHeight;
  const bool is_left_border = (head.x + cfg.size) == 0;
  const bool is_top_border = (head.y + cfg.size) == 0;

  const bool is_at_border = is_right_border || is_bottom_border || is_left_border || is_top_border;

  if (is_at_border) {  
    return true;
  }

  // Starting at 1 to exclude head as part of the body
  for (int i = 1; i < len; i++) {
    Snake body = snake[i];

    const bool is_self_coliding = body.x == head.x && body.y == head.y;

    if (is_self_coliding) {
      return true;
    }
  }

  return false;
}

bool reset(Snake *snake, Food *food, int *len, char *current_direction, char *input_direction, Config cfg) {
  if (IsKeyPressed(KEY_R)) {
    // Snake
    *len = 1;
    snake = realloc(snake, sizeof(Snake) * *len);
    snake[0].x = cfg.screenWidth / 2;
    snake[0].y = cfg.screenHeight / 2;

    // Food
    food->x = -1;
    food->y = -1;

    *current_direction = '_';
    *input_direction = '_';

    return true;
  } else {
    return false;
  }
}

void draw_snake (Snake *snake, int len, Config cfg) {
  for (int i = 0; i < len; i++) {
    DrawRectangle(snake[i].x, snake[i].y, cfg.size, cfg.size, RED);
    DrawRectangleLines(snake[i].x, snake[i].y, cfg.size, cfg.size, BLACK);
  }
}

void draw_game_over(Config cfg) {

  const char* game_over = "GAME OVER!";
  const char* retry = "Press R to retry";

  const int go_font_size = 40;
  const int r_font_size = 20;

  const int go_text_width = MeasureText(game_over, go_font_size);
  const int r_text_width = MeasureText(retry, r_font_size);

  DrawText(game_over, (cfg.screenWidth - go_text_width) / 2 , cfg.screenHeight / 2 - go_font_size / 2, go_font_size, RED);
  DrawText(retry, (cfg.screenWidth - r_text_width) / 2 , (cfg.screenHeight / 2 - r_font_size / 2) + 40, r_font_size, RED);
}

void draw_food(Food food, Config cfg) {
  if (food.x == -1 && food.y == -1) {
    return;
  }

  DrawRectangle(food.x, food.y, cfg.size, cfg.size, BLUE);
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