#include "raylib.h"

int main()
{
  // Window Dimensions
  const int windowWidth = 512;
  const int windowHeight = 380;

  // Initialize the Window
  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // Accel due to gravity (pixels/s/s
  const int gravity = 1000;

  // Scarfy variables
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  Rectangle scarfyRec;
  scarfyRec.width = scarfy.width / 6;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;
  Vector2 scarfyPos;
  // Character dimensions
  scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
  scarfyPos.y = windowHeight - scarfyRec.height;

  // Animation frame
  int frame = 0;
  // Amount of time before we update the animation frame
  const float updateTime = 1.00 / 12.00;
  float runningTime = 0;

  int velocity = 0;

  // is the character in the air?
  bool isInAir = false;
  // Jump velocity in pixels per second
  const int jumpVel = -600;

  // Nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
  // Nebula x velocity (pixels/second)
  int nebVel = -600;

  SetTargetFPS(120);
  while (!WindowShouldClose())
  {
    // Deltatime
    const float dT = GetFrameTime();

    // Start Drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // Perform ground check
    if (scarfyPos.y >= windowHeight - scarfyRec.height)
    {
      // Rectangle is on the ground
      velocity = 0;
      isInAir = false;
    }
    else
    {
      // Rectangle is in the air
      velocity += gravity * dT; // Apply gravity
      isInAir = true;
    }

    // Jump check
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    // Update nebula position
    nebPos.x += nebVel * dT;

    // Update scarfy position
    scarfyPos.y += velocity * dT;

    if (!isInAir)
    {
      // Update running time
      runningTime += dT;
      if (runningTime >= updateTime)
      {
        runningTime = 0.0;
        // Update animation frame
        scarfyRec.x = frame * scarfyRec.width;
        frame++;
        if (frame > 5)
        {
          frame = 0;
        }
      }
    }

    // Draw nebula
    DrawTextureRec(nebula, nebRec, nebPos, WHITE);

    // Draw scarfy
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // Stop Drawing
    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
}