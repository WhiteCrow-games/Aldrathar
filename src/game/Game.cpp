#include "game/Game.hpp"

#include <raylib.h>
#include <cmath>

void Game::initialize()
{
    elapsedTime_ = 0.0F;

    camera_.position = Vector3{0.0F, 5.0F, 8.5F};
    camera_.target = Vector3{0.0F, 1.0F, -0.3F};
    camera_.up = Vector3{0.0F, 1.0F, 0.0F};
    camera_.fovy = 48.0F;
    camera_.projection = CAMERA_PERSPECTIVE;
}

void Game::update(float fixedDeltaTime)
{
    elapsedTime_ += fixedDeltaTime;
}

void Game::render(float interpolation)
{
    (void)interpolation;

    BeginMode3D(camera_);
    drawRoom();
    drawFurniture();
    EndMode3D();

    DrawRectangle(5, 5, 188, 32, Color{0, 0, 0, 190});
    DrawText("ALDRATHAR // INTERIOR 01", 10, 10, 10, RAYWHITE);
    DrawText("CAMARA FIJA", 10, 22, 8, SKYBLUE);
    DrawText("WIP - PROTOTIPO 3D", 8, 226, 8, LIGHTGRAY);
}

void Game::drawRoom()
{
    const Color floorColor{43, 46, 48, 255};
    const Color wallColor{76, 79, 80, 255};
    const Color leftWallColor{100, 103, 103, 255};
    const Color darkWall{48, 51, 53, 255};
    const Color trimColor{105, 88, 65, 255};

    DrawPlane(
        Vector3{0.0F, 0.0F, 0.0F},
        Vector2{8.0F, 8.0F},
        floorColor
    );

    for (int i = -3; i <= 3; ++i) {
        const float p = static_cast<float>(i);

        DrawLine3D(
            Vector3{p, 0.012F, -3.8F},
            Vector3{p, 0.012F, 3.8F},
            Color{65, 67, 67, 255}
        );

        DrawLine3D(
            Vector3{-3.8F, 0.013F, p},
            Vector3{3.8F, 0.013F, p},
            Color{65, 67, 67, 255}
        );
    }

    // Pared trasera con hueco para la puerta.
    DrawCube(
        Vector3{-2.25F, 1.5F, -4.0F},
        3.5F, 3.0F, 0.25F,
        wallColor
    );

    DrawCube(
        Vector3{2.75F, 1.5F, -4.0F},
        2.5F, 3.0F, 0.25F,
        wallColor
    );

    DrawCube(
        Vector3{1.0F, 2.65F, -4.0F},
        1.0F, 0.7F, 0.25F,
        darkWall
    );

    // Pared izquierda: ahora más clara y con contorno.
    const Vector3 leftWallPosition{-4.0F, 1.5F, 0.0F};
    const Vector3 wallSize{0.25F, 3.0F, 8.0F};

    DrawCube(leftWallPosition,
             wallSize.x, wallSize.y, wallSize.z,
             leftWallColor);

    DrawCubeWires(leftWallPosition,
                  wallSize.x, wallSize.y, wallSize.z,
                  RAYWHITE);

    // Pared derecha.
    DrawCube(
        Vector3{4.0F, 1.5F, 0.0F},
        0.25F, 3.0F, 8.0F,
        wallColor
    );

    // Zócalos.
    DrawCube(
        Vector3{-3.84F, 0.18F, 0.0F},
        0.08F, 0.25F, 7.6F,
        trimColor
    );

    DrawCube(
        Vector3{3.84F, 0.18F, 0.0F},
        0.08F, 0.25F, 7.6F,
        trimColor
    );

    // Marco y puerta.
    DrawCube(
        Vector3{0.48F, 1.35F, -3.82F},
        0.12F, 2.7F, 0.12F,
        trimColor
    );

    DrawCube(
        Vector3{1.52F, 1.35F, -3.82F},
        0.12F, 2.7F, 0.12F,
        trimColor
    );

    DrawCube(
        Vector3{1.0F, 1.25F, -3.87F},
        0.88F, 2.5F, 0.08F,
        Color{25, 28, 30, 255}
    );

    DrawSphere(
        Vector3{1.32F, 1.2F, -3.78F},
        0.055F,
        GOLD
    );

    // Paneles frontales de la puerta.
    const Color doorInset{37, 39, 40, 255};
    const Color doorEdge{76, 66, 51, 255};

    DrawCube(
        Vector3{1.0F, 1.85F, -3.815F},
        0.62F, 0.72F, 0.025F,
        doorInset
    );

    DrawCube(
        Vector3{1.0F, 0.78F, -3.815F},
        0.62F, 0.62F, 0.025F,
        doorInset
    );

    DrawCube(
        Vector3{0.60F, 1.35F, -3.80F},
        0.035F, 2.45F, 0.025F,
        doorEdge
    );

    DrawCube(
        Vector3{1.40F, 1.35F, -3.80F},
        0.035F, 2.45F, 0.025F,
        doorEdge
    );

    // Indicador de advertencia junto a la entrada.
    DrawCube(
        Vector3{1.68F, 2.35F, -3.79F},
        0.12F, 0.20F, 0.045F,
        Color{32, 35, 35, 255}
    );

    DrawSphere(
        Vector3{1.68F, 2.37F, -3.755F},
        0.035F,
        Color{190, 42, 28, 255}
    );

    // Luminaria.
    DrawCube(
        Vector3{0.0F, 2.93F, 0.0F},
        0.75F, 0.08F, 0.35F,
        Color{105, 102, 85, 255}
    );

    DrawCube(
        Vector3{0.0F, 2.87F, 0.0F},
        0.58F, 0.035F, 0.22F,
        Color{180, 165, 115, 255}
    );
}

void Game::drawFurniture()
{
    const Color metal{48, 54, 58, 255};
    const Color metalEdge{91, 97, 99, 255};
    const Color crateColor{83, 65, 48, 255};

    // Mesa de trabajo.
    DrawCube(
        Vector3{-1.7F, 0.85F, -1.8F},
        2.0F, 0.12F, 0.9F,
        metalEdge
    );

    DrawCube(
        Vector3{-2.55F, 0.4F, -2.15F},
        0.09F, 0.8F, 0.09F, metal
    );
    DrawCube(
        Vector3{-0.85F, 0.4F, -2.15F},
        0.09F, 0.8F, 0.09F, metal
    );
    DrawCube(
        Vector3{-2.55F, 0.4F, -1.45F},
        0.09F, 0.8F, 0.09F, metal
    );
    DrawCube(
        Vector3{-0.85F, 0.4F, -1.45F},
        0.09F, 0.8F, 0.09F, metal
    );

    // Herramientas y piezas sobre la mesa.
    DrawCube(
        Vector3{-1.95F, 0.94F, -1.80F},
        0.48F, 0.045F, 0.28F,
        Color{65, 69, 68, 255}
    );

    DrawCube(
        Vector3{-1.92F, 0.985F, -1.80F},
        0.30F, 0.025F, 0.16F,
        Color{112, 91, 62, 255}
    );

    DrawCube(
        Vector3{-1.20F, 0.96F, -1.72F},
        0.34F, 0.035F, 0.08F,
        Color{128, 105, 68, 255}
    );

    DrawCube(
        Vector3{-1.20F, 0.985F, -1.72F},
        0.18F, 0.025F, 0.035F,
        metalEdge
    );

    DrawSphere(
        Vector3{-2.35F, 0.97F, -1.65F},
        0.055F,
        Color{166, 125, 55, 255}
    );

    // Cajas.
    DrawCube(
        Vector3{2.25F, 0.4F, 0.7F},
        1.0F, 0.8F, 0.85F,
        crateColor
    );

    DrawCubeWires(
        Vector3{2.25F, 0.4F, 0.7F},
        1.0F, 0.8F, 0.85F,
        Color{120, 94, 65, 255}
    );

    // Refuerzos frontales de la caja inferior.
    DrawCube(
        Vector3{2.25F, 0.18F, 1.135F},
        0.88F, 0.07F, 0.035F,
        Color{111, 81, 53, 255}
    );

    DrawCube(
        Vector3{2.25F, 0.55F, 1.135F},
        0.88F, 0.07F, 0.035F,
        Color{111, 81, 53, 255}
    );

    DrawCube(
        Vector3{1.78F, 0.40F, 1.14F},
        0.06F, 0.72F, 0.04F,
        Color{111, 81, 53, 255}
    );

    DrawCube(
        Vector3{2.72F, 0.40F, 1.14F},
        0.06F, 0.72F, 0.04F,
        Color{111, 81, 53, 255}
    );

    DrawCube(
        Vector3{2.1F, 1.15F, 0.65F},
        0.65F, 0.65F, 0.6F,
        Color{65, 51, 39, 255}
    );

    // Armario industrial.
    DrawCube(
        Vector3{-3.45F, 1.1F, -1.8F},
        0.7F, 2.2F, 1.2F,
        metal
    );

    DrawCubeWires(
        Vector3{-3.45F, 1.1F, -1.8F},
        0.7F, 2.2F, 1.2F,
        metalEdge
    );

    DrawCube(
        Vector3{-3.06F, 1.1F, -2.05F},
        0.035F, 0.25F, 0.04F,
        LIGHTGRAY
    );

    DrawCube(
        Vector3{-3.06F, 1.1F, -1.65F},
        0.035F, 0.25F, 0.04F,
        LIGHTGRAY
    );

    // Ventilación y placa de identificación del armario.
    DrawCube(
        Vector3{-3.06F, 1.72F, -1.80F},
        0.035F, 0.28F, 0.56F,
        Color{31, 36, 39, 255}
    );

    for (int i = 0; i < 4; ++i) {
        const float z = -2.00F + static_cast<float>(i) * 0.13F;

        DrawCube(
            Vector3{-3.035F, 1.72F, z},
            0.025F, 0.025F, 0.075F,
            metalEdge
        );
    }

    DrawCube(
        Vector3{-3.025F, 0.48F, -1.80F},
        0.035F, 0.08F, 0.38F,
        Color{105, 80, 48, 255}
    );

    const float pulse =
        0.65F + 0.35F * std::sin(elapsedTime_ * 2.0F);

    const unsigned char intensity =
        static_cast<unsigned char>(100.0F + 100.0F * pulse);

    DrawSphere(
        Vector3{-3.45F, 2.35F, -2.42F},
        0.09F,
        Color{intensity, 25, 20, 255}
    );
}
