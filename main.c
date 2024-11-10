#include "core.h"

int main(void) {
  srand(time(NULL));

  Config cfg = config();

  // Snake info
  int len = 1;
  char direction = cfg.directions.right;
  bool did_eat = false;

  // Initializing snake
  Snake *snake = malloc(sizeof(Snake) * len); 
  Snake head = { cfg.screenWidth/2, cfg.screenHeight/2 };
  snake[0] = head;

  // Current food position
  Food food = { -1, -1 };

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
      const bool no_food = food.x == -1 && food.y == -1;

      if (no_food) {
        food = spawn_food(food, cfg);
      }

      const bool is_eating = snake[0].x == food.x && snake[0].y == food.y;
      
      if (is_eating) {
        food = spawn_food(food, cfg);
        did_eat = true;
      }

      // Changing direction if user presses arrow
      direction = change_direction(direction, cfg.directions);

      // Moving the snake based on tick and speed
      if (tick % cfg.speed == 0) {
        // If food was eaten, increase the length
        if (did_eat) {
          len++;
          snake = realloc(snake, sizeof(Snake) * len);
          did_eat = false;
        }

        // Shifting the snake forward
        for (int i = len - 1; i > 0; i--) {
          snake[i] = snake[i - 1];
        }

        move(direction, &snake[0], cfg);

        tick = 0;
      }

      draw_food(food, cfg);
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
// 2. Make sure food dosent spawn on the snake
// 4. Direction Change Handling