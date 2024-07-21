#include raylib.h

int main()
{
  // Window Dimensions
  const int windowWidth = 512;
  const int windowHeight = 380;

  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    // Start Drawing
    BeginDrawing();
    ClearBackground(White);

    // Stop Drawing
    EndDrawing();
  }

  CloseWindow();
}