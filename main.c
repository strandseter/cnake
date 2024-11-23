#include "core.h"

int main(void) {
  srand(time(NULL));

  Config cfg = config();

  // Initializing snake
  int len = 1;
  Snake *snake = malloc(sizeof(Snake) * len); 
  Snake head = { cfg.screenWidth / 2, cfg.screenHeight / 2 };
  snake[0] = head;

  // Current food position
  Food food = { -1, -1 };

  // Game data
  int tick = 0;
  bool game_running = true;

  // Controls
  char current_direction = '_';
  char input_direction = '_';

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    if (game_running) {
      track_input(current_direction, &input_direction, cfg.directions);

      // Moving the snake based on tick and speed
      if (tick % cfg.speed == 0) {
        tick = 0; 

        current_direction = input_direction;

        if (is_no_food(food)) {
          food = spawn_food(food, snake, len, cfg);
        }
      
        if (is_eating(snake, food)) {
          // Increase length of snake
          len++;
          snake = realloc(snake, sizeof(Snake) * len);

          food = spawn_food(food, snake, len, cfg);
        }

        shift_body(snake, len);
        move_head(current_direction, &snake[0], cfg);
      }

      draw_food(food, cfg);
      draw_snake(snake, len, cfg);

      tick++;
    }

    if (game_over(snake, len, cfg)) {
      draw_game_over(cfg);
      game_running = reset(snake, &food, &len, &current_direction, &input_direction, cfg);
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