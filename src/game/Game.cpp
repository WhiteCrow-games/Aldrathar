#include "game/Game.hpp"
#include <algorithm>
#include <cmath>

namespace {
constexpr float JOYSTICK_RADIUS = 28.0F;
constexpr float KNOB_RADIUS = 11.0F;
constexpr float TRUNK_RADIUS = 0.28F; // Solo tronco bloquea, no follaje
constexpr float PLAYER_COLLISION_RADIUS = 0.25F;
constexpr float TREE_COLLISION_RADIUS =
    TRUNK_RADIUS + PLAYER_COLLISION_RADIUS;

bool pointInCircle(Vector2 point, Vector2 center, float radius)
{
    const float dx = point.x - center.x;
    const float dy = point.y - center.y;
    return dx * dx + dy * dy <= radius * radius;
}

bool blockedAt(float x, float z)
{
    if (x < -13.0F || x > 13.0F || z < -13.0F || z > 13.0F) return true;

    // Solo troncos bloquean, follaje no
    const Vector2 trunks[] = {
        {-5.0F, -3.0F}, {5.5F, -4.0F}, {-6.0F, 3.0F},
        {6.5F, 4.0F}, {-4.5F, 7.0F}, {4.5F, 9.0F}
    };
    for (const Vector2& t : trunks) {
        if (pointInCircle(Vector2{x, z}, t, TREE_COLLISION_RADIUS)) return true;
    }

    const bool insideHouseLength = z > -6.95F && z < -3.0F;
    if (insideHouseLength && (std::abs(x - 2.43F) < 0.40F || std::abs(x + 2.43F) < 0.40F)) return true;
    if (std::abs(z + 6.68F) < 0.40F && std::abs(x) < 2.85F) return true;
    if (std::abs(z + 3.25F) < 0.40F && std::abs(x) > 0.17F && std::abs(x) < 2.85F) return true;
    return false;
}

bool isPlayerInsideHouse(Vector3 p) {
    return p.x > -2.3F && p.x < 2.3F && p.z > -6.5F && p.z < -3.3F;
}


unsigned char getFoliageAlpha(Vector3 player, Vector3 tree) {
    float dx = player.x - tree.x;
    float dz = player.z - tree.z;
    float dist = std::sqrt(dx*dx + dz*dz);
    // Si estas a <1.8m detrás del árbol, se desvanece
    if (dist < 1.8F) return 90;
    if (dist < 2.8F) return 170;
    return 255;
}
}

void Game::initialize()
{
    elapsedTime_ = 0.0F;
    movementVelocityX_ = 0.0F;
    movementVelocityZ_ = 0.0F;
    player_.GetPosition() = Vector3{0.0F, 0.0F, 3.0F};
    dragon_.SetPosition(Vector3{-3.8F, 0.0F, -1.5F});
    isometric_ = false;
    firstPerson_ = false;
    cameraPitch_ = 0.0F;
    joystickTouchId_ = -1;
    cameraTouchId_ = -1;
    cameraTouchWasDown_ = false;
    cameraOrbitAngle_ = 0.0F;
    cameraTouchLastX_ = 0.0F;
    cameraTouchLastY_ = 0.0F;
    cameraTouchIsButton_ = false;
    touchMove_ = Vector2{0.0F, 0.0F};
    camera_.up = Vector3{0.0F, 1.0F, 0.0F};
    isInsideHouse_ = false;
    updateCamera();
}

void Game::updateCamera()
{
    const Vector3 p = player_.GetPosition();
    camera_.up = Vector3{0.0F, 1.0F, 0.0F};

    // Isométrica fija: no utiliza el ángulo de primera/tercera persona.
    if (isometric_) {
        constexpr float angle = 0.785398163F;
        constexpr float radius = 12.0F;
        constexpr float height = 10.5F;

        camera_.target = Vector3{p.x, p.y + 0.65F, p.z};
        camera_.position = Vector3{
            p.x + std::sin(angle) * radius,
            p.y + height,
            p.z + std::cos(angle) * radius
        };
        camera_.projection = CAMERA_ORTHOGRAPHIC;
        camera_.fovy = 16.0F;
        return;
    }

    const float yaw = cameraOrbitAngle_;
    const float pitch = cameraPitch_;
    const Vector3 forward{
        std::sin(yaw) * std::cos(pitch),
        std::sin(pitch),
        -std::cos(yaw) * std::cos(pitch)
    };

    if (firstPerson_) {
        camera_.position = Vector3{p.x, p.y + 1.55F, p.z};
        camera_.target = Vector3{
            camera_.position.x + forward.x,
            camera_.position.y + forward.y,
            camera_.position.z + forward.z
        };
        camera_.projection = CAMERA_PERSPECTIVE;
        camera_.fovy = 70.0F;
        return;
    }

    // Tercera persona: perspectiva detrás del jugador.
    const Vector3 focus{p.x, p.y + 1.2F, p.z};
    constexpr float distance = 5.0F;
    camera_.target = focus;
    camera_.position = Vector3{
        focus.x - forward.x * distance,
        focus.y - forward.y * distance + 0.5F,
        focus.z - forward.z * distance
    };
    camera_.projection = CAMERA_PERSPECTIVE;
    camera_.fovy = 55.0F;
}

void Game::update(float fixedDeltaTime)
{
    elapsedTime_ += fixedDeltaTime;

    dragon_.Update(fixedDeltaTime);
    isInsideHouse_ = isPlayerInsideHouse(player_.GetPosition());

    const auto toggleIsometric = [this]() {
        if (!isometric_) {
            savedCameraOrbitAngle_ = cameraOrbitAngle_;
            savedCameraPitch_ = cameraPitch_;
            hasSavedCameraOrientation_ = true;
            isometric_ = true;
        } else {
            if (hasSavedCameraOrientation_) {
                cameraOrbitAngle_ = savedCameraOrbitAngle_;
                cameraPitch_ = savedCameraPitch_;
            }
            isometric_ = false;
        }
    };

    const auto leaveIsometric = [this]() {
        if (isometric_) {
            if (hasSavedCameraOrientation_) {
                cameraOrbitAngle_ = savedCameraOrbitAngle_;
                cameraPitch_ = savedCameraPitch_;
            }
            isometric_ = false;
        }
    };

    if (IsKeyPressed(KEY_V)) {
        leaveIsometric();
        firstPerson_ = !firstPerson_;
    }
    if (IsKeyPressed(KEY_I)) {
        toggleIsometric();
    }
    float moveX = 0.0F, moveZ = 0.0F;
    if (IsKeyDown(KEY_A)) moveX -= 1.0F;
    if (IsKeyDown(KEY_D)) moveX += 1.0F;
    if (IsKeyDown(KEY_W)) moveZ -= 1.0F;
    if (IsKeyDown(KEY_S)) moveZ += 1.0F;

    const int touchCount = GetTouchPointCount();
    const bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    const Vector2 mousePosition = GetMousePosition();
    bool joystickFound = false; bool cameraFound = false;

    if (touchCount > 0) {
        for (int i = 0; i < touchCount; ++i) {
            const int id = GetTouchPointId(i);
            const Vector2 screen = GetTouchPosition(i);
            const float sx = screen.x * 320.0F / static_cast<float>(GetScreenWidth());
            const float sy = screen.y * 240.0F / static_cast<float>(GetScreenHeight());
            const Vector2 p{sx, sy};
            if (id == joystickTouchId_) {
                joystickFound = true;
                const float dx = p.x - joystickCenter_.x; const float dy = p.y - joystickCenter_.y;
                const float distance = std::sqrt(dx * dx + dy * dy);
                const float scale = distance > JOYSTICK_RADIUS ? JOYSTICK_RADIUS / distance : 1.0F;
                joystickKnob_ = Vector2{joystickCenter_.x + dx * scale, joystickCenter_.y + dy * scale};
                touchMove_.x = std::clamp(dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
                touchMove_.y = std::clamp(dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            }
            if (id == cameraTouchId_) {
                cameraFound = true;

                if (!cameraTouchIsButton_ && !isometric_) {
                    const float dragX = p.x - cameraTouchLastX_;
                    const float dragY = p.y - cameraTouchLastY_;

                    cameraOrbitAngle_ += dragX * 0.01F;
                    cameraPitch_ = std::clamp(
                        cameraPitch_ - dragY * 0.01F,
                        -1.2F, 1.2F
                    );

                    cameraTouchLastX_ = p.x;
                    cameraTouchLastY_ = p.y;
                }
            }

            if (joystickTouchId_ == -1 && p.x < 100.0F && p.y > 125.0F) {
                joystickTouchId_ = id; joystickFound = true;
                const float dx = p.x - joystickCenter_.x; const float dy = p.y - joystickCenter_.y;
                const float distance = std::sqrt(dx * dx + dy * dy);
                const float scale = distance > JOYSTICK_RADIUS ? JOYSTICK_RADIUS / distance : 1.0F;
                joystickKnob_ = Vector2{joystickCenter_.x + dx * scale, joystickCenter_.y + dy * scale};
                touchMove_.x = std::clamp(dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
                touchMove_.y = std::clamp(dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            }

            if (cameraTouchId_ == -1 && p.x > 160.0F) {
                cameraTouchId_ = id;
                cameraFound = true;
                cameraTouchLastX_ = p.x;
                cameraTouchLastY_ = p.y;
                cameraTouchIsButton_ = p.x > 255.0F && p.y < 34.0F;

                if (cameraTouchIsButton_) {
                    if (p.x >= 291.0F) {
                        toggleIsometric();
                    } else {
                        leaveIsometric();
                        firstPerson_ = !firstPerson_;
                    }
                }
            }
        }
    } else if (mouseDown) {
        const Vector2 p{
            mousePosition.x * 320.0F /
                static_cast<float>(GetScreenWidth()),
            mousePosition.y * 240.0F /
                static_cast<float>(GetScreenHeight())
        };

        if (p.x < 100.0F && p.y > 125.0F) {
            const float dx = p.x - joystickCenter_.x;
            const float dy = p.y - joystickCenter_.y;
            const float distance = std::sqrt(dx * dx + dy * dy);
            const float scale =
                distance > JOYSTICK_RADIUS
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
        } else if (p.x > 160.0F) {
            if (!cameraTouchWasDown_) {
                // Inicio de pulsación: CAM cambia de modo una sola vez.
                cameraTouchLastX_ = p.x;
                cameraTouchLastY_ = p.y;
                cameraTouchIsButton_ =
                    p.x > 255.0F && p.y < 34.0F;

                if (cameraTouchIsButton_) {
                    if (p.x >= 291.0F) {
                        toggleIsometric();
                    } else {
                        leaveIsometric();
                        firstPerson_ = !firstPerson_;
                    }
                }
            } else if (!cameraTouchIsButton_ && !isometric_) {
                // Solo primera persona: arrastrar para mirar alrededor.
                const float dragX = p.x - cameraTouchLastX_;
                const float dragY = p.y - cameraTouchLastY_;

                cameraOrbitAngle_ += dragX * 0.01F;
                cameraPitch_ = std::clamp(
                    cameraPitch_ - dragY * 0.01F,
                    -1.2F, 1.2F
                );

                cameraTouchLastX_ = p.x;
                cameraTouchLastY_ = p.y;
            }

            cameraTouchWasDown_ = true;
        }
    } else {
        cameraTouchWasDown_ = false;
        cameraTouchIsButton_ = false;
    }

    if (touchCount > 0) {
        cameraTouchWasDown_ = cameraFound;
    }

    if (!joystickFound) {
        joystickTouchId_ = -1;
        joystickKnob_ = joystickCenter_;
        touchMove_ = Vector2{0.0F, 0.0F};
    }

    if (!cameraFound) {
        cameraTouchId_ = -1;
        cameraTouchIsButton_ = false;
    }

    // El joystick expresa movimiento relativo a la cámara.
    moveX += touchMove_.x;
    moveZ += touchMove_.y;

    const float localX = moveX;
    const float localZ = moveZ;

    if (!isometric_) {
        // Primera y tercera persona comparten orientación de movimiento.
        // W/arriba debe avanzar exactamente en esa dirección.
        const float yaw = cameraOrbitAngle_;
        moveX = localX * std::cos(yaw) - localZ * std::sin(yaw);
        moveZ = localX * std::sin(yaw) + localZ * std::cos(yaw);
    } else {
        // Movimiento isométrico fijo, independiente del giro libre.
        constexpr float isoYaw = 0.785398163F;
        moveX = localX * std::cos(isoYaw) + localZ * std::sin(isoYaw);
        moveZ = -localX * std::sin(isoYaw) + localZ * std::cos(isoYaw);
    }

    const float inputLength = std::sqrt(moveX * moveX + moveZ * moveZ);

    constexpr float speed = 3.0F;
    constexpr float acceleration = 12.0F;
    constexpr float braking = 16.0F;

    float desiredX = 0.0F;
    float desiredZ = 0.0F;

    if (inputLength > 0.001F) {
        desiredX = (moveX / inputLength) * speed;
        desiredZ = (moveZ / inputLength) * speed;
    }

    const float deltaX = desiredX - movementVelocityX_;
    const float deltaZ = desiredZ - movementVelocityZ_;
    const float deltaLength = std::sqrt(deltaX * deltaX + deltaZ * deltaZ);
    const float rate = inputLength > 0.001F ? acceleration : braking;
    const float maxChange = rate * fixedDeltaTime;

    if (deltaLength > maxChange && deltaLength > 0.0F) {
        const float scale = maxChange / deltaLength;
        movementVelocityX_ += deltaX * scale;
        movementVelocityZ_ += deltaZ * scale;
    } else {
        movementVelocityX_ = desiredX;
        movementVelocityZ_ = desiredZ;
    }

    const float nextX =
        player_.GetPosition().x + movementVelocityX_ * fixedDeltaTime;

    if (!blockedAt(nextX, player_.GetPosition().z)) {
        player_.GetPosition().x = nextX;
    } else {
        movementVelocityX_ = 0.0F;
    }

    const float nextZ =
        player_.GetPosition().z + movementVelocityZ_ * fixedDeltaTime;

    if (!blockedAt(player_.GetPosition().x, nextZ)) {
        player_.GetPosition().z = nextZ;
    } else {
        movementVelocityZ_ = 0.0F;
    }

    const float actualSpeed = std::sqrt(
        movementVelocityX_ * movementVelocityX_ +
        movementVelocityZ_ * movementVelocityZ_
    );

    player_.SetMoving(actualSpeed > 0.05F);

    if (actualSpeed > 0.05F) {
        player_.SetFacingDirection(movementVelocityX_, movementVelocityZ_);
    }

    playerEntity_->Update(fixedDeltaTime);

    updateCamera();
}

void Game::render(float interpolation)
{
    (void)interpolation;
    BeginMode3D(camera_);
    drawOutdoor();
    drawHouse();
    drawTrees();
    drawBushes();
    dragon_.Draw();

    if (isometric_ || !firstPerson_) {
        drawCharacter();
    }
    EndMode3D();

    // Sin rectángulo negro: texto compacto directamente sobre el juego.
    DrawText("ALDRATHAR", 5, 5, 8, RAYWHITE);
    DrawText(
        isometric_ ? "CAM: I" : (firstPerson_ ? "CAM: 1P" : "CAM: 3P"),
        5, 16, 7, SKYBLUE
    );
    DrawText(
        isInsideHouse_ ? "INTERIOR: FADE" : "EXTERIOR",
        5, 26, 7, isInsideHouse_ ? GREEN : LIGHTGRAY
    );
    DrawText("TRONCOS: COLISION", 5, 36, 6, LIGHTGRAY);
    DrawText("PROTOTIPO 3D", 5, 226, 6, LIGHTGRAY);
    drawTouchControls();
}

void Game::drawTouchControls()
{
    // Joystick original conservado.
    DrawCircleV(
        joystickCenter_, JOYSTICK_RADIUS + 5.0F,
        Color{0, 0, 0, 100}
    );
    DrawCircleV(
        joystickCenter_, JOYSTICK_RADIUS,
        Color{170, 180, 170, 100}
    );
    DrawCircleLines(
        static_cast<int>(joystickCenter_.x),
        static_cast<int>(joystickCenter_.y),
        JOYSTICK_RADIUS,
        Color{220, 225, 210, 210}
    );
    DrawCircleV(
        joystickKnob_, KNOB_RADIUS,
        Color{225, 225, 210, 220}
    );

    // Botón 1P/3P: representa la vista contraria a la activa.
    DrawCircleV(Vector2{273.0F, 16.0F}, 9.0F, Color{35, 42, 38, 170});
    DrawCircleLines(273, 16, 8.0F, RAYWHITE);
    DrawText(firstPerson_ ? "3" : "1", 270, 11, 10, RAYWHITE);

    // Botón independiente de cámara isométrica.
    DrawCircleV(
        Vector2{302.0F, 16.0F}, 9.0F,
        isometric_ ? Color{150, 170, 120, 230}
                   : Color{35, 42, 38, 170}
    );
    DrawCircleLines(302, 16, 8.0F, RAYWHITE);
    DrawText("I", 299, 11, 10, RAYWHITE);

    if (!isometric_) {
        DrawText("ARRASTRA PARA MIRAR", 208, 226, 6,
                 Color{230, 230, 220, 170});
    }
}

void Game::drawOutdoor()
{
    DrawPlane(Vector3{0.0F, -0.05F, 0.0F}, Vector2{32.0F, 32.0F}, Color{63, 78, 53, 255});
    DrawCube(Vector3{0.0F, 0.01F, 4.0F}, 2.2F, 0.04F, 18.0F, Color{116, 94, 67, 255});
}
void Game::drawHouse()
{
    const bool inside = isInsideHouse_;
    const Color wall{113, 104, 85, 255};
    const Color roof{67, 43, 39, 255};
    const Color dark{36, 39, 38, 255};

    // Ocultar las superficies que quedan entre la cámara y el interior.
    // Es más fiable que usar transparencia con el búfer de profundidad.
    const bool hideFront = inside && camera_.position.z > -5.0F;
    const bool hideBack = inside && !hideFront;
    const bool hideRight = inside && camera_.position.x > 0.0F;
    const bool hideLeft = inside && !hideRight;

    if (!hideLeft)
        DrawCube(Vector3{-2.43F, 1.35F, -5.0F},
                 0.14F, 2.7F, 3.5F, wall);

    if (!hideRight)
        DrawCube(Vector3{2.43F, 1.35F, -5.0F},
                 0.14F, 2.7F, 3.5F, wall);

    if (!hideBack)
        DrawCube(Vector3{0.0F, 1.35F, -6.68F},
                 5.0F, 2.7F, 0.14F, wall);

    if (!hideFront) {
        DrawCube(Vector3{-1.49F, 1.35F, -3.25F},
                 2.02F, 2.7F, 0.14F, wall);
        DrawCube(Vector3{1.49F, 1.35F, -3.25F},
                 2.02F, 2.7F, 0.14F, wall);
        DrawCube(Vector3{0.0F, 2.2F, -3.25F},
                 0.96F, 1.0F, 0.14F, wall);

        DrawCube(Vector3{-0.56F, 0.85F, -3.18F},
                 0.12F, 1.7F, 0.08F, dark);
        DrawCube(Vector3{-1.65F, 1.55F, -3.16F},
                 0.85F, 0.75F, 0.08F, Color{53, 83, 91, 255});
        DrawCube(Vector3{1.65F, 1.55F, -3.16F},
                 0.85F, 0.75F, 0.08F, Color{53, 83, 91, 255});
        DrawCube(Vector3{0.0F, 0.05F, -3.1F},
                 2.0F, 0.12F, 0.7F, Color{90, 83, 70, 255});
    }

    // El techo permanece fuera de la casa y se oculta al entrar.
    if (!inside) {
        DrawCube(Vector3{-1.25F, 3.0F, -5.0F},
                 2.9F, 0.18F, 4.1F, roof);
        DrawCube(Vector3{1.25F, 3.0F, -5.0F},
                 2.9F, 0.18F, 4.1F, roof);
    }
}

void Game::drawTrees()
{
    const Vector3 positions[] = {{-5.0F, 0.0F, -3.0F},{5.5F, 0.0F, -4.0F},{-6.0F, 0.0F, 3.0F},{6.5F, 0.0F, 4.0F},{-4.5F, 0.0F, 7.0F},{4.5F, 0.0F, 9.0F}};
    for (const Vector3& p : positions) {
        // Tronco siempre solido y bloquea
        DrawCylinder(Vector3{p.x, 0.8F, p.z}, TRUNK_RADIUS, TRUNK_RADIUS*0.8F, 1.6F, 8, Color{91, 65, 43, 255});
        // Copa con fade si jugador detrás
        unsigned char alpha = getFoliageAlpha(player_.GetPosition(), p);
        Color leaf1{42, 76, 43, alpha};
        Color leaf2{52, 88, 47, alpha};
        DrawSphere(Vector3{p.x, 2.0F, p.z}, 1.0F, leaf1);
        DrawSphere(Vector3{p.x + 0.35F, 2.35F, p.z}, 0.65F, leaf2);
    }
}
void Game::drawBushes()
{
    // Arbustos no bloquean, pero tambien hacen fade
    const Vector3 bushes[] = {{2.0F,0,-1.0F},{-2.0F,0,1.0F},{3.5F,0,6.0F}};
    for (auto &b : bushes) {
        unsigned char alpha = getFoliageAlpha(player_.GetPosition(), b);
        DrawSphere(Vector3{b.x, 0.3F, b.z}, 0.45F, Color{55,85,45,alpha});
        DrawSphere(Vector3{b.x+0.2F,0.4F,b.z}, 0.35F, Color{65,95,50,alpha});
    }
}
void Game::drawCharacter()
{
    playerEntity_->Draw();
}

void Game::drawRoom() { DrawPlane(Vector3{0.0F, 0.0F, 0.0F}, Vector2{8.0F, 8.0F}, Color{43, 46, 48, 255}); }
void Game::drawFurniture() { DrawCube(Vector3{-1.7F, 0.85F, -1.8F}, 2.0F, 0.12F, 0.9F, Color{91, 97, 99, 255}); }
