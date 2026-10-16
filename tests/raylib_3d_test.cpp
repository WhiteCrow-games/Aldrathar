
#include <raylib.h>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Aldrathar - 3D test");
    if (!IsWindowReady())
        return 1;

    Camera3D camera{};
    camera.position = {4.0f, 4.0f, 6.0f};
    camera.target = {0.0f, 1.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{15, 17, 25, 255});

        BeginMode3D(camera);

        DrawPlane(
            Vector3{0.0f, 0.0f, 0.0f},
            Vector2{10.0f, 10.0f},
            DARKGRAY
        );

        DrawCube(
            Vector3{0.0f, 1.0f, 0.0f},
            1.0f, 2.0f, 1.0f,
            MAROON
        );

        DrawCubeWires(
            Vector3{0.0f, 1.0f, 0.0f},
            1.0f, 2.0f, 1.0f,
            RAYWHITE
        );

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("ALDRATHAR | 3D CAMERA TEST", 20, 20, 20, RAYWHITE);
        DrawText("Fixed camera - press ESC to exit", 20, 420, 16, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
