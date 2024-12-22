#include <raylib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
  InitWindow(600, 400, "CNAKE - Intro");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(RAYWHITE);

      
      const int fontSize = 20;
      const int y = 150;  // Moved up from 200
      const int spacing = 20; // Increased spacing for bigger gaps between lines

      const char *label_title = "Title:";
      const char *label_name = "My name:";
      const char *label_user = "Github/edX:";
      const char *label_address = "City/Country:";
      const char *label_date = "Date:";

      const char *value_title = "CNAKE";
      const char *value_name = "Anders Strandseter";
      const char *value_user = "strandseter/anders_strandseter";
      const char *value_address = "Fredrikstad/Norway";
      const char *value_date = "2024-12-22";

      // Find the widest label to align all labels
      int maxLabelWidth = 0;
      maxLabelWidth = fmax(maxLabelWidth, MeasureText(label_title, fontSize));
      maxLabelWidth = fmax(maxLabelWidth, MeasureText(label_name, fontSize));
      maxLabelWidth = fmax(maxLabelWidth, MeasureText(label_user, fontSize));
      maxLabelWidth = fmax(maxLabelWidth, MeasureText(label_address, fontSize));
      maxLabelWidth = fmax(maxLabelWidth, MeasureText(label_date, fontSize));

      const int labelX = 50; // Fixed position from left edge
      const int valueX = labelX + maxLabelWidth + 10; // 10 pixels padding between label and value

      // Draw labels aligned to the right
      DrawText(label_title, labelX, y, fontSize, RED);
      DrawText(label_name, labelX, y + spacing, fontSize, RED);
      DrawText(label_user, labelX, y + spacing * 2, fontSize, RED);
      DrawText(label_address, labelX, y + spacing * 3, fontSize, RED);
      DrawText(label_date, labelX, y + spacing * 4, fontSize, RED);

      // Draw values
      DrawText(value_title, valueX, y, fontSize, RED);
      DrawText(value_name, valueX, y + spacing, fontSize, RED);
      DrawText(value_user, valueX, y + spacing * 2, fontSize, RED);
      DrawText(value_address, valueX, y + spacing * 3, fontSize, RED);
      DrawText(value_date, valueX, y + spacing * 4, fontSize, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}