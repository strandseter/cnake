#include "core.h"

int main(void) {
  srand(time(NULL));

  Config cfg = config();

  // The snake
  Vector2 head = { (float)cfg.screenWidth/2, (float)cfg.screenHeight/2 };
  Vector2 *body = malloc(sizeof(Vector2) * 0); 

  // Snake controls
  int len = 0;
  char direction = cfg.directions.right;

  // Curren food position
  Vector2 food = { -1, -1 };

  // Game data
  int tick = 0;
  bool game_running = true;
  bool did_eat = false;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    //debug_print(head, current_direction);

    if (game_over(head, cfg)) {
      game_running = false;
    }

    if (game_running) {
      // Spawn initial food
      if (food.x == -1 && food.y == -1) {
        food.x = (rand() % (cfg.screenWidth / cfg.size)) * cfg.size;
        food.y = (rand() % (cfg.screenHeight / cfg.size)) * cfg.size;
      }

      // Spawn food if eaten
      if (head.x == food.x && head.y == food.y) {
        food.x = (rand() % (cfg.screenWidth / cfg.size)) * cfg.size;
        food.y = (rand() % (cfg.screenHeight / cfg.size)) * cfg.size;

        did_eat = true;
      }

      // Changing direction if user presses arrow
      change_direction(&direction, cfg.directions);

      // Moving the snake based on tick and speed
      if (tick % cfg.speed == 0) {
        // If food was eaten, increase the length
        if (did_eat) {
          len++;
          body = realloc(body, sizeof(Vector2) * len);
          did_eat = false;
        }

        // Shifting body one index to the right to make space for next
        for (int i = len - 1; i > 0; i--) {
          body[i] = body[i - 1];
        }

        // Adding the previous head as first part of body
        Vector2 prev;
        prev.x = head.x;
        prev.y = head.y;
        body[0] = prev;

        move(direction, &head, cfg);
      }

      // Draw
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


// TODO
// 1. Initial Body Allocation. Remove head??
// 2. Food Spawning Logic. Make sure food dosent spawn on the snake
// 3. Self-Collision
// 4. Direction Change Handling