#include "core.h"

void debug_print(Vector2 pos, char direction) {
  printf("Current direction: %c\n", direction);
  printf("x: %.0f, y: %.0f\n", pos.x, pos.y);
}

Config config() {
  Config config;

  Directions directions;
  directions.right = 'R';
  directions.down = 'D';
  directions.left = 'L';
  directions.up = 'U';

  config.directions = directions;

  config.screenWidth = 800;
  config.screenHeight = 450;

  InitWindow(config.screenWidth, config.screenHeight, "CS50");

  SetTargetFPS(60);

  return config;
}

void change_direction(char *current_direction, Directions directions) {
  if (IsKeyPressed(KEY_RIGHT)) *current_direction = directions.right;
  if (IsKeyPressed(KEY_DOWN)) *current_direction = directions.down;
  if (IsKeyPressed(KEY_LEFT)) *current_direction = directions.left;
  if (IsKeyPressed(KEY_UP)) *current_direction = directions.up;
}

void move(char current_direction, Vector2 *pos, Config cfg) {
  if (current_direction == cfg.directions.right) pos->x += 2.0f;
  if (current_direction == cfg.directions.down) pos->y += 2.0f;
  if (current_direction == cfg.directions.left) pos->x -= 2.0f;
  if (current_direction == cfg.directions.up) pos->y -= 2.0f;
}

bool game_over(Vector2 pos, Config cfg) {
  int fontSize = 40;
  char* gameOver = "GAME OVER!";

  int textWidth = MeasureText(gameOver, fontSize);

  bool isWidthinWindow = pos.x != 0 && pos.y != 0;

  if (!isWidthinWindow) {
    DrawText(gameOver, (cfg.screenWidth - textWidth) / 2 , cfg.screenHeight / 2 - fontSize / 2, fontSize, RED);
  
    return true;
  }

  return false;
}