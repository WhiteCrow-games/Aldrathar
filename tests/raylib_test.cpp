
#include <raylib.h>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Aldrathar - raylib test");

    if (!IsWindowReady())
        return 1;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{12, 14, 22, 255});

        DrawText("ALDRATHAR", 30, 30, 36, RAYWHITE);
        DrawText("raylib 6.0 | Termux ARM64", 32, 80, 20, SKYBLUE);

        DrawRectangle(30, 130, 200, 120, DARKGRAY);
        DrawRectangleLines(30, 130, 200, 120, GREEN);

        DrawText("2D renderer: OK", 45, 175, 18, GREEN);
        DrawText("Press ESC to exit", 30, 400, 18, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
