#include "core.h"

int main(void) {
  srand(time(NULL));

  Config cfg = config();

  char current_direction = cfg.directions.right;
  bool is_game_running = true;

  Vector2 head = { (float)cfg.screenWidth/2, (float)cfg.screenHeight/2 };
  Vector2 *body = malloc(sizeof(Vector2) * 0); 

  Vector2 food = { -1, -1 };

  int len = 0;
  int tick = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    //debug_print(head, current_direction);

    if (game_over(head, cfg)) {
      is_game_running = false;
    }

    if (is_game_running) {
      if (tick % cfg.speed == 0) {
        // Shifting body one index to the right to make space for next
        for (int i = len - 1; i > 0; i--) {
          body[i] = body[i - 1];
        }

        // Adding the previous head as first part of body
        Vector2 prev;
        prev.x = head.x;
        prev.y = head.y;
        body[0] = prev;

        move(current_direction, &head, cfg);
      }

      change_direction(&current_direction, cfg.directions);

      // Spawn food
      if (food.x == -1 && food.y == -1) {
        food.x = (rand() % (cfg.screenWidth / cfg.size)) * cfg.size;
        food.y = (rand() % (cfg.screenHeight / cfg.size)) * cfg.size;
      }

      if (head.x == food.x && head.y == food.y) {
        food.x = (rand() % (cfg.screenWidth / cfg.size)) * cfg.size;
        food.y = (rand() % (cfg.screenHeight / cfg.size)) * cfg.size;

        len ++;
        body = realloc(body, sizeof(Vector2) * len + 1);
      }

      // Draw food
      DrawRectangle(food.x, food.y, cfg.size, cfg.size, BLUE);
      draw_snake_head(head, cfg);
      draw_snake_body(body, len, cfg);

      tick++;
    }

    EndDrawing();
  }

  free(body);

  CloseWindow();

  return 0;
};
