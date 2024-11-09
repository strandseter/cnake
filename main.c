#include "core.h"

int main(void) {
  Config cfg = config();


  char current_direction = cfg.directions.right;
  bool is_game_running = true;

  Vector2 head = { (float)cfg.screenWidth/2, (float)cfg.screenHeight/2 };
  Vector2* body = malloc(sizeof(Vector2) * 1000); 

  int length = 0;
  int tick = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    debug_print(head, current_direction);

    if (game_over(head, cfg)) {
      is_game_running = false;
    }

    if (is_game_running) {
      if (tick % cfg.speed == 0) {
        Vector2 prev;
        prev.x = head.x;
        prev.y = head.y;
        body[tick] = prev;

        move(current_direction, &head, cfg);
      }

      change_direction(&current_direction, cfg.directions);

      draw_snake_head(head, cfg);
      draw_snake_body(body, length, cfg);

      tick++;
    }

    EndDrawing();
  }

  free(body);

  CloseWindow();

  return 0;
};
