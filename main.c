#include "core.h"

int main(void) {
  srand(time(NULL));

  Config cfg = config();

  // Snake info
  int len = 1;
  char direction = cfg.directions.right;
  bool did_eat = false;

  // Initializing snake
  Snake *snake = malloc(sizeof(Snake) * 1); 
  Snake head = { cfg.screenWidth/2, cfg.screenHeight/2 };
  snake[0] = head;

  // Current food position
  Snake food = { -1, -1 };

  // Game data
  int tick = 0;
  bool game_running = true;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    if (game_over(snake, len, cfg)) {
      draw_game_over(cfg);
      game_running = false;
    }

    if (game_running) {
      // Spawn initial food
      if (food.x == -1 && food.y == -1) {
        food.x = (rand() % (cfg.screenWidth / cfg.size)) * cfg.size;
        food.y = (rand() % (cfg.screenHeight / cfg.size)) * cfg.size;
      }

      // Spawn food if eaten
      if (snake[0].x == food.x && snake[0].y == food.y) {
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
          snake = realloc(snake, sizeof(Snake) * len);
          did_eat = false;
        }

        // Shifting snake one index to the right to make space for next
        for (int i = len - 1; i > 0; i--) {
          snake[i] = snake[i - 1];
        }

        // Adding the previous head as the second part of the snake
        Snake prev;
        prev.x = snake[0].x;
        prev.y = snake[0].y;
        snake[1] = prev;

        move(direction, &snake[0], cfg);
      }

      // Draw
      DrawRectangle(food.x, food.y, cfg.size, cfg.size, BLUE);
      draw_snake(snake, len, cfg);

      tick++;
    }

    EndDrawing();
  }

  free(snake);

  CloseWindow();

  return 0;
};


// TODO
// 2. Food Spawning Logic. Make sure food dosent spawn on the snake
// 3. Self-Collision
// 4. Direction Change Handling