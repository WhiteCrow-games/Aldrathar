#include "game/Game.hpp"

#include <algorithm>
#include <cmath>

namespace {
constexpr float JOYSTICK_RADIUS = 28.0F;
constexpr float KNOB_RADIUS = 11.0F;

bool pointInCircle(Vector2 point, Vector2 center, float radius)
{
    const float dx = point.x - center.x;
    const float dy = point.y - center.y;
    return dx * dx + dy * dy <= radius * radius;
}

bool blockedAt(float x, float z)
{
    constexpr float playerRadius = 0.32F;

    // Limites del terreno.
    if (x < -13.0F || x > 13.0F ||
        z < -13.0F || z > 13.0F) {
        return true;
    }

    // Troncos de los arboles.
    const Vector2 trees[] = {
        {-5.0F, -3.0F},
        {5.5F, -4.0F},
        {-6.0F, 3.0F},
        {6.5F, 4.0F},
        {-4.5F, 7.0F},
        {4.5F, 9.0F}
    };

    for (const Vector2& tree : trees) {
        if (pointInCircle(Vector2{x, z}, tree, 0.52F)) {
            return true;
        }
    }

    // Paredes laterales de la casa.
    const bool insideHouseLength = z > -6.95F && z < -3.0F;
    if (insideHouseLength &&
        (std::abs(x - 2.43F) < 0.40F ||
         std::abs(x + 2.43F) < 0.40F)) {
        return true;
    }

    // Pared trasera.
    if (std::abs(z + 6.68F) < 0.40F &&
        std::abs(x) < 2.85F) {
        return true;
    }

    // Pared frontal: deja libre el hueco de la puerta.
    if (std::abs(z + 3.25F) < 0.40F &&
        std::abs(x) > 0.17F &&
        std::abs(x) < 2.85F) {
        return true;
    }

    return false;
}
}

void Game::initialize()
{
    elapsedTime_ = 0.0F;
    playerPosition_ = Vector3{0.0F, 0.0F, 3.0F};
    isometric_ = false;
    joystickTouchId_ = -1;
    cameraTouchId_ = -1;
    cameraTouchWasDown_ = false;
    touchMove_ = Vector2{0.0F, 0.0F};

    camera_.up = Vector3{0.0F, 1.0F, 0.0F};
    updateCamera();
}

void Game::updateCamera()
{
    camera_.target = Vector3{
        playerPosition_.x,
        playerPosition_.y + 0.8F,
        playerPosition_.z
    };

    if (isometric_) {
        camera_.position = Vector3{
            playerPosition_.x + 10.0F,
            playerPosition_.y + 12.0F,
            playerPosition_.z + 10.0F
        };

        camera_.projection = CAMERA_ORTHOGRAPHIC;
        camera_.fovy = 17.0F;
    } else {
        camera_.position = Vector3{
            playerPosition_.x,
            playerPosition_.y + 5.0F,
            playerPosition_.z + 8.5F
        };

        camera_.target.z -= 1.0F;
        camera_.projection = CAMERA_PERSPECTIVE;
        camera_.fovy = 48.0F;
    }
}

void Game::update(float fixedDeltaTime)
{
    elapsedTime_ += fixedDeltaTime;

    // Teclado físico: se mantiene como alternativa.
    if (IsKeyPressed(KEY_V)) {
        isometric_ = !isometric_;
    }

    float moveX = 0.0F;
    float moveZ = 0.0F;

    if (IsKeyDown(KEY_A)) moveX -= 1.0F;
    if (IsKeyDown(KEY_D)) moveX += 1.0F;
    if (IsKeyDown(KEY_W)) moveZ -= 1.0F;
    if (IsKeyDown(KEY_S)) moveZ += 1.0F;

    // Joystick táctil usando las coordenadas del render interno 320x240.
    const int touchCount = GetTouchPointCount();
    const bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    const Vector2 mousePosition = GetMousePosition();

    bool joystickFound = false;
    bool cameraFound = false;

    if (touchCount > 0) {
        for (int i = 0; i < touchCount; ++i) {
            const int id = GetTouchPointId(i);
            const Vector2 screen = GetTouchPosition(i);

            // Convertir coordenadas de ventana a coordenadas internas.
            const float sx = screen.x * 320.0F /
                static_cast<float>(GetScreenWidth());
            const float sy = screen.y * 240.0F /
                static_cast<float>(GetScreenHeight());

            const Vector2 p{sx, sy};

            if (id == joystickTouchId_) {
                joystickFound = true;
                const float dx = p.x - joystickCenter_.x;
                const float dy = p.y - joystickCenter_.y;
                const float distance = std::sqrt(dx * dx + dy * dy);
                const float scale = distance > JOYSTICK_RADIUS
                    ? JOYSTICK_RADIUS / distance : 1.0F;

                joystickKnob_ = Vector2{
                    joystickCenter_.x + dx * scale,
                    joystickCenter_.y + dy * scale
                };

                touchMove_.x = std::clamp(
                    dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
                touchMove_.y = std::clamp(
                    dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            }

            if (id == cameraTouchId_) {
                cameraFound = true;
            }

            if (joystickTouchId_ == -1 &&
                p.x < 100.0F && p.y > 125.0F) {
                joystickTouchId_ = id;
                joystickFound = true;
                joystickKnob_ = p;

                const float dx = p.x - joystickCenter_.x;
                const float dy = p.y - joystickCenter_.y;
                const float distance = std::sqrt(dx * dx + dy * dy);
                const float scale = distance > JOYSTICK_RADIUS
                    ? JOYSTICK_RADIUS / distance : 1.0F;

                joystickKnob_ = Vector2{
                    joystickCenter_.x + dx * scale,
                    joystickCenter_.y + dy * scale
                };

                touchMove_.x = std::clamp(
                    dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
                touchMove_.y = std::clamp(
                    dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            }

            if (cameraTouchId_ == -1 &&
                p.x > 255.0F && p.y > 145.0F) {
                cameraTouchId_ = id;
                cameraFound = true;
            }
        }
    } else if (mouseDown) {
        // Compatibilidad con ratón y pantallas que emulan ratón.
        const Vector2 p{
            mousePosition.x * 320.0F /
                static_cast<float>(GetScreenWidth()),
            mousePosition.y * 240.0F /
                static_cast<float>(GetScreenHeight())
        };

        if (p.x > 255.0F && p.y > 145.0F) {
            if (!cameraTouchWasDown_) {
                isometric_ = !isometric_;
            }
            cameraTouchWasDown_ = true;
        } else if (p.x < 100.0F && p.y > 125.0F) {
            const float dx = p.x - joystickCenter_.x;
            const float dy = p.y - joystickCenter_.y;
            const float distance = std::sqrt(dx * dx + dy * dy);
            const float scale = distance > JOYSTICK_RADIUS
                ? JOYSTICK_RADIUS / distance : 1.0F;

            joystickKnob_ = Vector2{
                joystickCenter_.x + dx * scale,
                joystickCenter_.y + dy * scale
            };
            touchMove_.x = std::clamp(
                dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
            touchMove_.y = std::clamp(
                dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            joystickFound = true;
        }
    } else {
        cameraTouchWasDown_ = false;
    }

    if (touchCount > 0) {
        cameraTouchWasDown_ = cameraFound;

        if (cameraFound && cameraTouchId_ >= 0) {
            // Solo alternar al iniciar el toque, no cada fotograma.
            static int previousCameraId = -1;
            if (previousCameraId != cameraTouchId_) {
                isometric_ = !isometric_;
            }
            previousCameraId = cameraTouchId_;
        }
    }

    if (!joystickFound) {
        joystickTouchId_ = -1;
        joystickKnob_ = joystickCenter_;
        touchMove_ = Vector2{0.0F, 0.0F};
    }

    if (!cameraFound) {
        cameraTouchId_ = -1;
    }

    moveX += touchMove_.x;
    moveZ += touchMove_.y;

    const float length = std::sqrt(moveX * moveX + moveZ * moveZ);

    if (length > 0.0F) {
        constexpr float speed = 3.0F;

        const float stepX =
            (moveX / length) * speed * fixedDeltaTime;
        const float stepZ =
            (moveZ / length) * speed * fixedDeltaTime;

        // Resolver cada eje por separado evita quedar pegado
        // a una pared al intentar moverse en diagonal.
        const float nextX = playerPosition_.x + stepX;
        if (!blockedAt(nextX, playerPosition_.z)) {
            playerPosition_.x = nextX;
        }

        const float nextZ = playerPosition_.z + stepZ;
        if (!blockedAt(playerPosition_.x, nextZ)) {
            playerPosition_.z = nextZ;
        }
    }

    updateCamera();
}

void Game::render(float interpolation)
{
    (void)interpolation;

    BeginMode3D(camera_);
    drawOutdoor();
    drawHouse();
    drawTrees();
    drawCharacter();
    EndMode3D();

    DrawRectangle(5, 5, 205, 47, Color{0, 0, 0, 210});
    DrawText("ALDRATHAR // OUTDOOR", 10, 10, 10, RAYWHITE);

    if (isometric_) {
        DrawText("CAMARA: ISOMETRICA", 10, 24, 8, SKYBLUE);
    } else {
        DrawText("CAMARA: TERCERA PERSONA", 10, 24, 8, SKYBLUE);
    }

    DrawText("TACTIL: JOYSTICK + CAMARA", 10, 36, 8, LIGHTGRAY);
    DrawText("PROTOTIPO 3D", 8, 226, 8, LIGHTGRAY);

    drawTouchControls();
}

void Game::drawTouchControls()
{
    // Joystick virtual.
    DrawCircleV(joystickCenter_, JOYSTICK_RADIUS + 5.0F,
                Color{0, 0, 0, 100});
    DrawCircleV(joystickCenter_, JOYSTICK_RADIUS,
                Color{170, 180, 170, 100});
    DrawCircleLines(
        static_cast<int>(joystickCenter_.x),
        static_cast<int>(joystickCenter_.y),
        JOYSTICK_RADIUS,
        Color{220, 225, 210, 210}
    );
    DrawCircleV(joystickKnob_, KNOB_RADIUS,
                Color{225, 225, 210, 220});

    // Botón para cambiar la cámara.
    const Vector2 buttonCenter{282.0F, 184.0F};
    DrawCircleV(buttonCenter, 24.0F, Color{0, 0, 0, 120});
    DrawCircleV(buttonCenter, 19.0F, Color{110, 130, 120, 210});
    DrawCircleLines(282, 184, 19.0F, RAYWHITE);
    DrawText("CAM", 269, 180, 9, RAYWHITE);
}
void Game::drawOutdoor()
{
    DrawPlane(
        Vector3{0.0F, -0.05F, 0.0F},
        Vector2{32.0F, 32.0F},
        Color{63, 78, 53, 255}
    );

    DrawCube(
        Vector3{0.0F, 0.01F, 4.0F},
        2.2F, 0.04F, 18.0F,
        Color{116, 94, 67, 255}
    );

    for (int i = -5; i <= 5; ++i) {
        const float x = static_cast<float>(i) * 2.5F;

        DrawCube(
            Vector3{x, 0.0F, -2.0F},
            0.8F, 0.025F, 0.6F,
            Color{52, 68, 45, 255}
        );
    }
}

void Game::drawHouse()
{
    const Color wall{113, 104, 85, 255};
    const Color roof{67, 43, 39, 255};
    const Color dark{36, 39, 38, 255};

    // La estructura se divide en paredes para permitir entrar.
    // Pared lateral izquierda y derecha.
    DrawCube(
        Vector3{-2.43F, 1.35F, -5.0F},
        0.14F, 2.7F, 3.5F, wall
    );

    DrawCube(
        Vector3{2.43F, 1.35F, -5.0F},
        0.14F, 2.7F, 3.5F, wall
    );

    // Pared trasera.
    DrawCube(
        Vector3{0.0F, 1.35F, -6.68F},
        5.0F, 2.7F, 0.14F, wall
    );

    // Pared frontal con abertura para la puerta.
    DrawCube(
        Vector3{-1.49F, 1.35F, -3.25F},
        2.02F, 2.7F, 0.14F, wall
    );

    DrawCube(
        Vector3{1.49F, 1.35F, -3.25F},
        2.02F, 2.7F, 0.14F, wall
    );

    // Parte superior del marco de la puerta.
    DrawCube(
        Vector3{0.0F, 2.2F, -3.25F},
        0.96F, 1.0F, 0.14F, wall
    );

    // Techo.
    DrawCube(
        Vector3{-1.25F, 3.0F, -5.0F},
        2.9F, 0.18F, 4.1F, roof
    );

    DrawCube(
        Vector3{1.25F, 3.0F, -5.0F},
        2.9F, 0.18F, 4.1F, roof
    );

    // Hoja de la puerta entreabierta, fuera del paso central.
    DrawCube(
        Vector3{-0.56F, 0.85F, -3.18F},
        0.12F, 1.7F, 0.08F, dark
    );

    // Ventanas frontales.
    DrawCube(
        Vector3{-1.65F, 1.55F, -3.16F},
        0.85F, 0.75F, 0.08F,
        Color{53, 83, 91, 255}
    );

    DrawCube(
        Vector3{1.65F, 1.55F, -3.16F},
        0.85F, 0.75F, 0.08F,
        Color{53, 83, 91, 255}
    );

    // Escalon.
    DrawCube(
        Vector3{0.0F, 0.05F, -3.1F},
        2.0F, 0.12F, 0.7F,
        Color{90, 83, 70, 255}
    );
}

void Game::drawTrees()
{
    const Vector3 positions[] = {
        {-5.0F, 0.0F, -3.0F},
        {5.5F, 0.0F, -4.0F},
        {-6.0F, 0.0F, 3.0F},
        {6.5F, 0.0F, 4.0F},
        {-4.5F, 0.0F, 7.0F},
        {4.5F, 0.0F, 9.0F}
    };

    for (const Vector3& p : positions) {
        DrawCylinder(
            Vector3{p.x, 0.8F, p.z},
            0.22F, 0.16F, 1.6F, 6,
            Color{91, 65, 43, 255}
        );

        DrawSphere(
            Vector3{p.x, 2.0F, p.z},
            1.0F, Color{42, 76, 43, 255}
        );

        DrawSphere(
            Vector3{p.x + 0.35F, 2.35F, p.z},
            0.65F, Color{52, 88, 47, 255}
        );
    }
}

void Game::drawCharacter()
{
    DrawCube(
        Vector3{playerPosition_.x, 0.9F, playerPosition_.z},
        0.55F, 1.1F, 0.35F,
        Color{65, 82, 104, 255}
    );

    DrawSphere(
        Vector3{playerPosition_.x, 1.65F, playerPosition_.z},
        0.25F, Color{184, 145, 112, 255}
    );

    DrawCube(
        Vector3{playerPosition_.x - 0.14F, 0.25F, playerPosition_.z},
        0.16F, 0.5F, 0.18F, DARKGRAY
    );

    DrawCube(
        Vector3{playerPosition_.x + 0.14F, 0.25F, playerPosition_.z},
        0.16F, 0.5F, 0.18F, DARKGRAY
    );
}

void Game::drawRoom()
{
    DrawPlane(
        Vector3{0.0F, 0.0F, 0.0F},
        Vector2{8.0F, 8.0F},
        Color{43, 46, 48, 255}
    );

    DrawCube(
        Vector3{0.0F, 1.5F, -4.0F},
        8.0F, 3.0F, 0.25F,
        Color{76, 79, 80, 255}
    );

    DrawCube(
        Vector3{-4.0F, 1.5F, 0.0F},
        0.25F, 3.0F, 8.0F,
        Color{100, 103, 103, 255}
    );

    DrawCube(
        Vector3{4.0F, 1.5F, 0.0F},
        0.25F, 3.0F, 8.0F,
        Color{76, 79, 80, 255}
    );
}

void Game::drawFurniture()
{
    DrawCube(
        Vector3{-1.7F, 0.85F, -1.8F},
        2.0F, 0.12F, 0.9F,
        Color{91, 97, 99, 255}
    );

    DrawCube(
        Vector3{2.25F, 0.4F, 0.7F},
        1.0F, 0.8F, 0.85F,
        Color{83, 65, 48, 255}
    );

    const float pulse = 0.65F + 0.35F * std::sin(elapsedTime_ * 2.0F);
    const auto intensity = static_cast<unsigned char>(100.0F + 100.0F * pulse);

    DrawSphere(
        Vector3{-3.45F, 2.35F, -2.42F},
        0.09F, Color{intensity, 25, 20, 255}
    );
}
