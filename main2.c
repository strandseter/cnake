#include <raylib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Structs

typedef struct {
  int size;
  int speed;
  int screenWidth;
  int screenHeight;
} Config;

typedef struct {
  int x;
  int y;
} Vector;

typedef enum {
    RIGHT, 
    DOWN, 
    LEFT, 
    UP,
    NONE,
} Direction;

typedef enum {
  START,
  RUNNING,
  OVER,
} State;

// Global variables

Config config;

int len;

Vector *snake;
Vector food;

Direction input;
Direction direction;

State state;

// Prototypes
void init_config();
void init_game();
void track_input();
void change_direction();
void spawn_food();
void game_over();
void eat();
void move();
void draw();

int main(void)
{
  init_config();
  init_game();

  int tick = 0;

  while (!WindowShouldClose()) 
  {
    BeginDrawing();

    track_input();

    if (tick % config.speed == 0)
    {
      tick = 0;

      change_direction();
      eat();
      move();
      game_over();
    }

    draw();

    tick++;
  }

  free(snake);

  CloseWindow();
  return 0;
}

void game_over()
{
  const bool is_right_border = snake[0].x == config.screenWidth;
  const bool is_bottom_border = snake[0].y == config.screenHeight;
  const bool is_left_border = (snake[0].x + config.size) == 0;
  const bool is_top_border = (snake[0].y + config.size) == 0;

  const bool is_at_border = is_right_border || is_bottom_border || is_left_border || is_top_border;

  if (is_at_border)
  {
    state = OVER;
    return;
  }

  for (int i = 1; i < len; i++) 
  {
    const bool is_self_coliding = snake[i].x == snake[0].x && snake[i].y == snake[0].y;

    if (is_self_coliding) 
    {
      state = OVER;
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

  printf("%i\n", direction);

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
  snake = realloc(snake, sizeof(Vector) * len);
  if (snake == NULL) {
    fprintf(stderr, "Failed to reallocate memory for snake\n");
    exit(EXIT_FAILURE);
  }

  spawn_food();
}

void spawn_food()
{
  int x = (rand() % (config.screenWidth / config.size)) * config.size;
  int y = (rand() % (config.screenHeight / config.size)) * config.size;

  for (int i = 0; i < len; i++) {
    while (snake[i].x == x && snake[i].y == y) {
      x = (rand() % (config.screenWidth / config.size)) * config.size;
      y = (rand() % (config.screenHeight / config.size)) * config.size;
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
  if (state != START) return;

  const char* start = "Press ARROW to start";
  const int font_size = 20;

  DrawText(start, (config.screenWidth -  MeasureText(start, font_size)) / 2 , (config.screenHeight / 2 - font_size / 2) - 40, font_size, RED);
}

void draw_food()
{
  DrawRectangle(food.x, food.y, config.size, config.size, BLUE);
}

void draw_snake() 
{
  for (int i = 0; i < len; i++) 
  {
    DrawRectangle(snake[i].x, snake[i].y, config.size, config.size, RED);
    DrawRectangleLines(snake[i].x, snake[i].y, config.size, config.size, BLACK);
  }
}

void draw() 
{
  BeginDrawing();
  ClearBackground(RAYWHITE);
    //draw_start();
    //draw_game_over();
    draw_food();
    draw_snake(); 
    
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
  state = START;

  input = NONE;
  direction = NONE;

  len = 1;
  snake = malloc(sizeof(Vector) * len); 
  Vector head = { config.screenWidth / 2, config.screenHeight / 2 };
  snake[0] = head;

  if (snake == NULL) {
    // Handle memory allocation failure
    fprintf(stderr, "Failed to allocate memory for snake\n");
    exit(EXIT_FAILURE);
  }

  spawn_food();
}

void init_config()
{
  srand(time(NULL));

  // Custom config
  config.size = 10;
  config.speed = 3;
  config.screenWidth = 400;
  config.screenHeight = 400;

  // Raylib
  InitWindow(config.screenWidth, config.screenHeight, "CNAKE");
  SetTargetFPS(60);
}
