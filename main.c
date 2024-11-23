#include "core.h"

int main(void) {
  srand(time(NULL));

  Config cfg = config();

  // Initializing snake
  int len = 1;
  Snake *snake = malloc(sizeof(Snake) * len); 
  Snake head = { cfg.screenWidth/2, cfg.screenHeight/2 };
  snake[0] = head;

  // Current food position
  Food food = { -1, -1 };

  // Game data
  int tick = 0;
  bool game_running = true;

  // Controls
  char current_direction = '_';
  char input_direction = '_';
  bool did_eat = false;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
  
    if (game_running) {
      const bool no_food = food.x == -1 && food.y == -1;

      if (no_food) {
        food = spawn_food(food, snake, len, cfg);
      }

      const bool is_eating = snake[0].x == food.x && snake[0].y == food.y;
      
      if (is_eating) {
        food = spawn_food(food, snake, len, cfg);
        did_eat = true;
      }
      
      track_input(current_direction, &input_direction, cfg.directions);

      // Moving the snake based on tick and speed
      if (tick % cfg.speed == 0) {
        tick = 0; 

        current_direction = input_direction;

        // If food was eaten, increase the length
        if (did_eat) {
          len++;
          snake = realloc(snake, sizeof(Snake) * len);
          did_eat = false;
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

      if (IsKeyPressed(KEY_R)) {
        // Restarting game state

        // Snake
        len = 1;
        snake = realloc(snake, sizeof(Snake) * len);

        snake[0].x = cfg.screenWidth / 2;
        snake[0].y = cfg.screenHeight / 2;

        // Food
        food.x = -1;
        food.y = -1;

        // Direction
        input_direction = '_';
        current_direction = '_';

        game_running = true;
      } else {
        game_running = false;
      }
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