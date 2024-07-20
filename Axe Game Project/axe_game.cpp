#include "raylib.h"

int main()
{
    // Init Window with Dimensions
    int width = 1280;
    int height = 720;
    InitWindow(width, height, "Axe Game");

    // Circle Coordinates
    int circle_x = width/2;
    int circle_y = height/2;
    int circle_radius = 25;
    // Circle Edges
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;

    // Axe Coordinates
    int axe_x = height;
    int axe_y = 0;
    int axe_length = 90;
    // Axe Edges
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;

    int direction = 8;

    bool collision_with_axe = 
        (b_axe_y >= u_circle_y) && 
        (u_axe_y <= b_circle_y) && 
        (r_axe_x >= l_circle_x) && 
        (l_axe_x <= r_circle_x);

    SetTargetFPS(144);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game Over Logic
        if (collision_with_axe)
        {
            DrawText("Game Over!", width/2 - 32, height/2 - 32, 32, RED);
        }
        else
        {
            // Game logic begins

            // Update the edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;
            // Update collision_with_axe
            collision_with_axe = 
                (b_axe_y >= u_circle_y) && 
                (u_axe_y <= b_circle_y) && 
                (r_axe_x >= l_circle_x) && 
                (l_axe_x <= r_circle_x);

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // Move the axe
            axe_y += direction;
            if(axe_y > height || axe_y < 0)
            {
                direction = -direction;
            }

            // Moving circle keybinds
            if (IsKeyDown(KEY_D) && circle_x < width)
            {
                circle_x += 8;
            }
            if (IsKeyDown(KEY_A) && circle_x > 0)
            {
                circle_x -= 8;
            }
            if (IsKeyDown(KEY_W) && circle_y > 0)
            {
                circle_y -= 8;
            }
            if (IsKeyDown(KEY_S) && circle_y < height)
            {
                circle_y += 8;
            }
        }
        // Game logic ends
        EndDrawing();
    }
}
