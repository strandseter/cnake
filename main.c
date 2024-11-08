#include "core.h"

int main(void) {
  Config cfg = config();

  Vector2 pos = { (float)cfg.screenWidth/2, (float)cfg.screenHeight/2 };

  char current_direction = cfg.directions.right;

  bool is_game_running = true;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    debug_print(pos, current_direction);

    if (game_over(pos, cfg)) {
      is_game_running = false;
    }

    if (is_game_running) {
      change_direction(&current_direction, cfg.directions);

      move(current_direction, &pos, cfg);
      draw_snake(pos, cfg);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
};
