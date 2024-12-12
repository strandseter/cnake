#include <raylib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Structs

typedef struct {
  int size;
  int speed;
  int mapWidth;
  int mapHeight;
  int windowWidth;
  int windowHeight;
} Config;

typedef struct {
  int x;
  int y;
} Pos;

typedef enum {
    RIGHT, 
    DOWN, 
    LEFT, 
    UP,
    NONE,
} Direction;

typedef enum {
  RUNNING,
  PAUSED,
  GAME_OVER,
} State;

// Global variables

Config config;

State state;

int len;

Pos *snake;
Pos food;

Direction input;
Direction direction;

// Prototypes

void init();
void track_input();
void change_direction();
void spawn_food();
void eat();
void move();
void game_over();
void draw_game();
void draw_game_over();
void reset_game();

int main(void)
{
  init();

  int tick = 0;

  while (!WindowShouldClose()) 
  {
    track_input();

    if (tick % config.speed == 0)
    {
      tick = 0;

      if (state == RUNNING)
      {
        change_direction();
        eat();
        move();
        game_over();
      }
      else 
      {
        reset_game();
      }
    }

    if (state == RUNNING)
    {
      draw_game();
    } 
    else 
    {
      draw_game_over();
    }

    tick++;
  }

  free(snake);

  CloseWindow();
  return 0;
}

void game_over()
{
  const bool is_right_border = snake[0].x == config.mapWidth;
  const bool is_bottom_border = snake[0].y == config.mapHeight;
  const bool is_left_border = (snake[0].x + config.size) == 0;
  const bool is_top_border = (snake[0].y + config.size) == 0;

  const bool is_at_border = is_right_border || is_bottom_border || is_left_border || is_top_border;

  if (is_at_border)
  {
    state = GAME_OVER;
    return;
  }

  for (int i = 1; i < len; i++) 
  {
    const bool is_self_coliding = snake[i].x == snake[0].x && snake[i].y == snake[0].y;

    if (is_self_coliding) 
    {
      state = GAME_OVER;
      return;
    }
  }
}

void move()
{
  for (int i = len - 1; i > 0; i--) 
  {
    snake[i] = snake[i - 1];
  }

  if (direction == RIGHT)
  {
    snake[0].x += config.size;
  }
  if (direction == DOWN)
  {
    snake[0].y += config.size;
  }
  if (direction == LEFT)
  {
    snake[0].x -= config.size;
  }
  if (direction == UP)
  {
    snake[0].y -= config.size;
  }
}

void eat()
{
  const bool is_eating = snake[0].x == food.x && snake[0].y == food.y;
  if (!is_eating) return;

  len++;

  snake = realloc(snake, sizeof(Pos) * len);

  if (snake == NULL) {
    fprintf(stderr, "Failed to reallocate memory for snake\n");
    exit(EXIT_FAILURE);
  }

  spawn_food();
}

void spawn_food()
{
  int x = (rand() % (config.mapWidth / config.size)) * config.size;
  int y = (rand() % (config.mapHeight / config.size)) * config.size;

  for (int i = 0; i < len; i++) {
    while (snake[i].x == x && snake[i].y == y) {
      x = (rand() % (config.mapWidth / config.size)) * config.size;
      y = (rand() % (config.mapHeight / config.size)) * config.size;
    }
  }

  food.x = x;
  food.y = y;
}

void change_direction()
{
  if (input == RIGHT && direction != LEFT)
  {
    direction = input;
  }
  if (input == DOWN && direction != UP)
  {
    direction = input;
  }
  if (input == LEFT && direction != RIGHT)
  {
    direction = input;
  }
  if (input == UP && direction != DOWN)
  {
    direction = input;
  }
} 

void draw_start()
{
  if (direction != NONE) return;
  
  const char* start = "Press ARROW to start";
  const int font_size = 20;

  DrawText(start, (config.mapWidth -  MeasureText(start, font_size)) / 2 , (config.mapHeight / 2 - font_size / 2) - 40, font_size, RED);
}

void draw_food()
{
  DrawRectangle(food.x, food.y, config.size, config.size, BLUE);
  DrawRectangleLines(food.x, food.y, config.size, config.size, BLACK);
}

void draw_snake() 
{
  for (int i = 0; i < len; i++) 
  {
    DrawRectangle(snake[i].x, snake[i].y, config.size, config.size, RED);
    DrawRectangleLines(snake[i].x, snake[i].y, config.size, config.size, BLACK);
  }
}

void draw_score()
{
  char score_text[50];
  snprintf(score_text, sizeof(score_text), "Score: %d", len);

  // Draw at bottom right
  DrawText(score_text, 10, config.windowHeight - 30, 20, BLACK);
}

void draw_border()
{
  DrawRectangleLines(0, 0, config.mapWidth, config.mapHeight, GRAY);
}

void draw_game() 
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

    draw_border();
    draw_start();
    draw_food();
    draw_snake(); 
    draw_score();
    
  EndDrawing();
}

void draw_game_over()
{
  int score = len;

  char score_text[50];
  snprintf(score_text, sizeof(score_text), "Score: %d", score);

  const char* game_over = "GAME OVER!";
  const char* retry = "Press R to retry";

  const int go_font_size = 40;
  const int s_font_size = 20;
  const int r_font_size = 20;

  const int go_text_width = MeasureText(game_over, go_font_size);
  const int s_text_width = MeasureText(score_text, s_font_size);
  const int r_text_width = MeasureText(retry, r_font_size);

  BeginDrawing();
  ClearBackground(RAYWHITE);

    DrawText(game_over, (config.mapWidth - go_text_width) / 2 , config.mapHeight / 2 - go_font_size / 2, go_font_size, RED);
    DrawText(score_text, (config.mapWidth - s_text_width) / 2 , (config.mapHeight / 2 - s_font_size / 2) + 40, s_font_size, RED);
    DrawText(retry, (config.mapWidth - r_text_width) / 2 , (config.mapHeight / 2 - r_font_size / 2) + 100, r_font_size, RED);
  
  EndDrawing();
}

void track_input()
{
  if (IsKeyPressed(KEY_RIGHT)) 
  {
    input = RIGHT;
  }
  if (IsKeyPressed(KEY_DOWN)) 
  {
    input = DOWN;
  }
  if (IsKeyPressed(KEY_LEFT)) 
  {
    input = LEFT;
  }
  if (IsKeyPressed(KEY_UP)) 
  {
    input = UP;
  }
}

void init_game()
{
  input = NONE;
  direction = NONE;

  state = RUNNING;

  len = 1;
  snake = malloc(sizeof(Pos) * len); 

  if (snake == NULL) {
    fprintf(stderr, "Failed to allocate memory for snake\n");
    exit(EXIT_FAILURE);
  }

  Pos head = { config.mapWidth / 2, config.mapHeight / 2 };
  snake[0] = head;

  spawn_food();
}

void init_config()
{
  srand(time(NULL));

  // Custom config
  config.size = 10;
  config.speed = 3;
  config.mapWidth = 440;
  config.mapHeight = 400;
  config.windowWidth = 440;
  config.windowHeight = 440;

  // Raylib
  InitWindow(config.windowWidth, config.windowHeight, "CNAKE");
  SetTargetFPS(60);
}

void init()
{
  init_config();
  init_game();
}

void reset_game()
{
  if (IsKeyPressed(KEY_R))
  {
    free(snake);
    init_game();
  }
}


// TODO:

//Score Display: Display the current score on the screen during gameplay.
//High Score Tracking: Save and display the highest score achieved.
//Levels or Difficulty Settings: Add different levels or difficulty settings that increase the game's complexity.
//Sound Effects: Add sound effects for actions like eating food or game over.
//Menu System: Implement a start menu, pause menu, and game over screen with options to restart or quit.
//Code Documentation: Add comments and documentation to explain the code and its functionality.
//Error Handling: Improve error handling and edge case management.