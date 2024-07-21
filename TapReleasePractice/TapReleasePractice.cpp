#include <raylib.h>
#include <chrono>
#include <deque>
#include <string>
#include <ctime>

using namespace std::chrono;

struct Attempt
{
    int duration;
    bool success;
};

int main() 
{
    const int defaultScreenWidth = 1080;
    const int defaultScreenHeight = 720;
    int screenWidth = defaultScreenWidth;
    int screenHeight = defaultScreenHeight;
    InitWindow(screenWidth, screenHeight, "Quick Tap Training");

    bool isButtonPressed = false;
    bool isSettingKey = false; // Flag for setting the key
    bool isChangingMs = false; // Flag for changing the millisecond value
    bool isSettingsMenuOpen = false; // Flag for settings menu
    bool showConfirmation = false; // Flag for showing confirmation message
    double confirmationStartTime = 0.0; // Time when the confirmation message is shown
    bool isChangingResolution = false; // Flag for changing resolution
    bool isChangingFullscreen = false; // Flag for changing fullscreen

    high_resolution_clock::time_point pressStartTime;
    high_resolution_clock::time_point releaseStartTime;

    int targetKey = KEY_SPACE; // Default key is space
    int maxPressDuration = 27; // Maximum duration in milliseconds
    const int maxVisibleEntries = 10; // Maximum number of log entries to show

    std::deque<Attempt> attemptLog; // To store the log of attempts
    int scrollPosition = 0; // Current scroll position

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw settings text
        const char* settingsText = "Settings";
        int settingsTextWidth = MeasureText(settingsText, 20);
        Vector2 mousePosition = GetMousePosition();

        // Check if mouse is hovering over the settings text
        bool isHoveringSettings = (mousePosition.x >= screenWidth - settingsTextWidth - 20 && mousePosition.x <= screenWidth - 20 &&
                                   mousePosition.y >= 20 && mousePosition.y <= 40);

        // Change text color if hovering
        Color settingsTextColor = isHoveringSettings ? RED : BLACK;
        DrawText(settingsText, screenWidth - settingsTextWidth - 20, 20, 20, settingsTextColor);

        // Check if settings text is clicked
        if (isHoveringSettings && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            isSettingsMenuOpen = !isSettingsMenuOpen;
        }

        if (isSettingsMenuOpen) 
        {
            // Draw settings menu background
            DrawRectangle(screenWidth / 2 - 150, screenHeight / 2 - 180, 300, 360, LIGHTGRAY);

            // Draw "Change Key" button
            const char* changeKeyText = "Change Key";
            int changeKeyTextWidth = MeasureText(changeKeyText, 20);
            bool isHoveringChangeKey = (mousePosition.x >= screenWidth / 2 - changeKeyTextWidth / 2 &&
                                        mousePosition.x <= screenWidth / 2 - changeKeyTextWidth / 2 + changeKeyTextWidth &&
                                        mousePosition.y >= screenHeight / 2 - 160 && mousePosition.y <= screenHeight / 2 - 140);
            Color changeKeyTextColor = isHoveringChangeKey ? RED : DARKGRAY;
            DrawText(changeKeyText, screenWidth / 2 - changeKeyTextWidth / 2, screenHeight / 2 - 160, 20, changeKeyTextColor);

            if (isHoveringChangeKey && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                isSettingKey = true;
                isChangingMs = false;
                isChangingResolution = false;
                isChangingFullscreen = false;
            }

            // Draw "Change ms" button
            const char* changeMsText = "Change ms";
            int changeMsTextWidth = MeasureText(changeMsText, 20);
            bool isHoveringChangeMs = (mousePosition.x >= screenWidth / 2 - changeMsTextWidth / 2 &&
                                       mousePosition.x <= screenWidth / 2 - changeMsTextWidth / 2 + changeMsTextWidth &&
                                       mousePosition.y >= screenHeight / 2 - 120 && mousePosition.y <= screenHeight / 2 - 100);
            Color changeMsTextColor = isHoveringChangeMs ? RED : DARKGRAY;
            DrawText(changeMsText, screenWidth / 2 - changeMsTextWidth / 2, screenHeight / 2 - 120, 20, changeMsTextColor);

            if (isHoveringChangeMs && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                isChangingMs = true;
                isSettingKey = false;
                isChangingResolution = false;
                isChangingFullscreen = false;
            }

            // Draw "Change Resolution" button
            const char* changeResText = "Change Resolution";
            int changeResTextWidth = MeasureText(changeResText, 20);
            bool isHoveringChangeRes = (mousePosition.x >= screenWidth / 2 - changeResTextWidth / 2 &&
                                        mousePosition.x <= screenWidth / 2 - changeResTextWidth / 2 + changeResTextWidth &&
                                        mousePosition.y >= screenHeight / 2 - 80 && mousePosition.y <= screenHeight / 2 - 60);
            Color changeResTextColor = isHoveringChangeRes ? RED : DARKGRAY;
            DrawText(changeResText, screenWidth / 2 - changeResTextWidth / 2, screenHeight / 2 - 80, 20, changeResTextColor);

            if (isHoveringChangeRes && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                isChangingResolution = true;
                isSettingKey = false;
                isChangingMs = false;
                isChangingFullscreen = false;
            }

            // Draw "Toggle Fullscreen" button
            const char* toggleFullscreenText = "Toggle Fullscreen";
            int toggleFullscreenTextWidth = MeasureText(toggleFullscreenText, 20);
            bool isHoveringToggleFullscreen = (mousePosition.x >= screenWidth / 2 - toggleFullscreenTextWidth / 2 &&
                                               mousePosition.x <= screenWidth / 2 - toggleFullscreenTextWidth / 2 + toggleFullscreenTextWidth &&
                                               mousePosition.y >= screenHeight / 2 - 40 && mousePosition.y <= screenHeight / 2 - 20);
            Color toggleFullscreenTextColor = isHoveringToggleFullscreen ? RED : DARKGRAY;
            DrawText(toggleFullscreenText, screenWidth / 2 - toggleFullscreenTextWidth / 2, screenHeight / 2 - 40, 20, toggleFullscreenTextColor);

            if (isHoveringToggleFullscreen && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                isChangingFullscreen = true;
                isSettingKey = false;
                isChangingMs = false;
                isChangingResolution = false;
            }

            // Draw "Close App" button
            const char* closeAppText = "Close App";
            int closeAppTextWidth = MeasureText(closeAppText, 20);
            bool isHoveringCloseApp = (mousePosition.x >= screenWidth / 2 - closeAppTextWidth / 2 &&
                                       mousePosition.x <= screenWidth / 2 - closeAppTextWidth / 2 + closeAppTextWidth &&
                                       mousePosition.y >= screenHeight / 2 && mousePosition.y <= screenHeight / 2 + 20);
            Color closeAppTextColor = isHoveringCloseApp ? RED : DARKGRAY;
            DrawText(closeAppText, screenWidth / 2 - closeAppTextWidth / 2, screenHeight / 2, 20, closeAppTextColor);

            if (isHoveringCloseApp && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                CloseWindow();
                return 0;
            }

            if (isSettingKey) 
            {
                DrawText("Press any key to set as the target key...", screenWidth / 2 - 140, screenHeight / 2 + 40, 20, DARKGRAY);

                for (int key = 32; key < 350; key++) 
                {
                    if (IsKeyPressed(key)) 
                    {
                        targetKey = key;
                        isSettingKey = false;
                        isSettingsMenuOpen = false;
                        showConfirmation = true;
                        confirmationStartTime = GetTime();
                        break;
                    }
                }
            } 
            else if (isChangingMs) 
            {
                DrawText("Use UP/DOWN keys to change milliseconds", screenWidth / 2 - 140, screenHeight / 2 + 40, 20, DARKGRAY);

                if (IsKeyPressed(KEY_UP)) 
                {
                    maxPressDuration++;
                }
                else if (IsKeyPressed(KEY_DOWN)) 
                {
                    maxPressDuration--;
                }

                DrawText(TextFormat("Current ms: %d", maxPressDuration), screenWidth / 2 - 60, screenHeight / 2 + 60, 20, DARKGRAY);
            }
            else if (isChangingResolution) 
            {
                DrawText("Use 1: 1080x720, 2: 1280x720, 3: 1920x1080", screenWidth / 2 - 140, screenHeight / 2 + 40, 20, DARKGRAY);

                if (IsKeyPressed(KEY_ONE)) 
                {
                    screenWidth = 1080;
                    screenHeight = 720;
                    SetWindowSize(screenWidth, screenHeight);
                    isChangingResolution = false;
                }
                else if (IsKeyPressed(KEY_TWO)) 
                {
                    screenWidth = 1280;
                    screenHeight = 720;
                    SetWindowSize(screenWidth, screenHeight);
                    isChangingResolution = false;
                }
                else if (IsKeyPressed(KEY_THREE)) 
                {
                    screenWidth = 1920;
                    screenHeight = 1080;
                    SetWindowSize(screenWidth, screenHeight);
                    isChangingResolution = false;
                }
            }
            else if (isChangingFullscreen) 
            {
                DrawText("Press F to toggle fullscreen mode", screenWidth / 2 - 140, screenHeight / 2 + 40, 20, DARKGRAY);

                if (IsKeyPressed(KEY_F)) 
                {
                    ToggleFullscreen();
                    isChangingFullscreen = false;
                }
            }
        } 
        else 
        {
            if (IsKeyPressed(targetKey)) 
            {
                isButtonPressed = true;
                pressStartTime = high_resolution_clock::now();
            }

            if (IsKeyReleased(targetKey) && isButtonPressed) 
            {
                isButtonPressed = false;
                releaseStartTime = high_resolution_clock::now();
                auto pressDuration = duration_cast<milliseconds>(releaseStartTime - pressStartTime).count();
                bool success = pressDuration <= maxPressDuration;

                // Add the attempt to the log
                attemptLog.push_back({pressDuration, success});

                // Adjust scroll position to make the latest entry visible
                if (attemptLog.size() > maxVisibleEntries) 
                {
                    scrollPosition = attemptLog.size() - maxVisibleEntries;
                } 
                else 
                {
                    scrollPosition = 0;
                }
            }

            // Scroll up
            if (IsKeyPressed(KEY_UP)) 
            {
                if (scrollPosition > 0) 
                {
                    scrollPosition--;
                }
            }

            // Scroll down
            if (IsKeyPressed(KEY_DOWN)) 
            {
                if (scrollPosition < (int)attemptLog.size() - maxVisibleEntries) 
                {
                    scrollPosition++;
                }
            }

            // Mouse wheel scrolling
            int wheelMove = GetMouseWheelMove();
            if (wheelMove > 0) 
            {
                if (scrollPosition > 0) 
                {
                    scrollPosition--;
                }
            } 
            else if (wheelMove < 0) 
            {
                if (scrollPosition < (int)attemptLog.size() - maxVisibleEntries) 
                {
                    scrollPosition++;
                }
            }

            DrawText("Press and release the target key quickly!", 150, 50, 20, DARKGRAY);

            int logY = 100; // Starting Y position for the log entries
            int entriesToShow = attemptLog.size() > maxVisibleEntries ? maxVisibleEntries : attemptLog.size();
            for (int i = 0; i < entriesToShow; i++) 
            {
                const Attempt& attempt = attemptLog[i + scrollPosition];
                std::string logEntry = "Duration: " + std::to_string(attempt.duration) + " ms - " + (attempt.success ? "Success" : "Fail");
                Color logColor = attempt.success ? GREEN : RED;
                DrawText(logEntry.c_str(), 150, logY, 20, logColor);
                logY += 30; // Move to the next line
            }

            DrawText("Use UP/DOWN arrows or mouse wheel to scroll through the log.", 150, screenHeight - 40, 20, DARKGRAY);
        }

        // Show confirmation message if a new key is set
        if (showConfirmation) 
        {
            DrawText(TextFormat("New target key set: %c", targetKey), screenWidth / 2 - 80, screenHeight / 2 + 60, 20, GREEN);
            if (GetTime() - confirmationStartTime > 3) // Show for 3 seconds
            {
                showConfirmation = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
