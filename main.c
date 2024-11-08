#include "core.h"

int main(void) {
  Config cfg = config();

  Vector2 pos = { (float)cfg.screenWidth/2, (float)cfg.screenHeight/2 };

  char current_direction = cfg.directions.right;

  while (!WindowShouldClose()) {
    debug_print(pos, current_direction);

    if (game_over(pos, cfg)) {
      continue;
    }

    change_direction(&current_direction, cfg.directions);

    move(current_direction, &pos, cfg);

    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle(pos.x, pos.y, 10, 10, RED);
    
    EndDrawing();
  }

  CloseWindow();

  return 0;
};
