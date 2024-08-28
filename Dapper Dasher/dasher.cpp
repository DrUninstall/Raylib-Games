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
  const float updateTimeGround = 1.00 / 12.00; // Faster on the ground
  const float updateTimeAir = 1.00 / 6.00;     // Slower in the air
  float runningTime = 0;

  int velocity = 0;

  // is the character in the air?
  bool isInAir = false;
  // Jump velocity in pixels per second
  const int jumpVel = -600;

  // Horizontal movement velocity in the air (slow)
  const float airMoveSpeed = 100.0f;

  // Nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
  Rectangle neb2Rec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  Vector2 neb2Pos{windowWidth * 2, windowHeight - nebRec.height};

  // Nebula anim variables
  int nebFrame{};
  const float nebUpdateTime = 1.0 / 12.0;
  float nebRunningTime{};
  int neb2Frame{};
  const float neb2UpdateTime = 1.0 / 16.0;
  float neb2RunningTime{};

  // Nebula x velocity (pixels/second)
  int nebVel = -200;

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
    neb2Pos.x += nebVel * dT;

    // Update scarfy position
    scarfyPos.y += velocity * dT;

    // Determine the update time based on whether scarfy is in the air or on the ground
    float currentUpdateTime = isInAir ? updateTimeAir : updateTimeGround;

    // Update scarfy's running time and animation frame
    runningTime += dT;
    if (runningTime >= currentUpdateTime)
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

    // Update nebula's running and animation frame
    nebRunningTime += dT;
    if (nebRunningTime >= nebUpdateTime)
    {
      nebRunningTime = 0.0;
      nebRec.x = nebFrame * nebRec.width;
      nebFrame++;
      if (nebFrame > 7)
      {
        nebFrame = 0;
      }
    }
    // Update 2nd nebula's running and animation frame
    neb2RunningTime += dT;
    if (neb2RunningTime >= nebUpdateTime)
    {
      neb2RunningTime = 0.0;
      neb2Rec.x = neb2Frame * neb2Rec.width;
      neb2Frame++;
      if (neb2Frame > 7)
      {
        neb2Frame = 0;
      }
    }

    // Draw nebula
    DrawTextureRec(nebula, nebRec, nebPos, WHITE);

    // Draw 2nd nebula
    DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

    // Draw scarfy
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // Stop Drawing
    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
}