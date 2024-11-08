#include <stdio.h>
#include <raylib.h>

int main(void) {
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "CS50");

  Vector2 pos = { (float)screenWidth/2, (float)screenHeight/2 };

  SetTargetFPS(60);

  int fontSize = 40;
  char* gameOver = "GAME OVER!";

  int textWidth = MeasureText(gameOver, fontSize);

  while (!WindowShouldClose()) {
    printf("x: %.0f, y: %.0f", pos.x, pos.y);

    bool isWidthinWindow = pos.x != 0 && pos.y != 0;

    if (!isWidthinWindow) {
      DrawText(gameOver, (screenWidth - textWidth) / 2 , screenHeight / 2 - fontSize / 2, fontSize, RED);
    }

    printf("%d\n", isWidthinWindow); // prints 1

    if (IsKeyDown(KEY_RIGHT)) pos.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) {
      if (isWidthinWindow) {
        pos.x -= 2.0f;
      }
    }
    if (IsKeyDown(KEY_UP)) pos.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) pos.y += 2.0f;

    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle(pos.x, pos.y, 10, 10, RED);
    
    EndDrawing();
  }

  CloseWindow();

  return 0;
};