#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include "game/Player.hpp"
#include "game/DragonEntity.hpp"

class Game {
public:
    void initialize();
    void update(float fixedDeltaTime);
    void render(float interpolation);
    Camera3D getCamera() const { return camera_; }
private:
    void updateCamera();
    void drawTouchControls();
    void drawOutdoor();
    void drawHouse();
    void drawTrees();
    void drawBushes();
    void drawCharacter();
    void drawRoom();
    void drawFurniture();
    Camera3D camera_{};
    Aldrathar::Player player_{};
    Aldrathar::Entity* playerEntity_{&player_};
    float elapsedTime_{0.0f};
    float movementVelocityX_{0.0F};
    float movementVelocityZ_{0.0F};
    bool isometric_{false};
    Vector2 joystickCenter_{48.0f, 192.0f};
    Vector2 joystickKnob_{48.0f, 192.0f};
    Vector2 touchMove_{0,0};
    int joystickTouchId_{-1};
    int cameraTouchId_{-1};
    bool cameraTouchWasDown_{false};
    float cameraOrbitAngle_{0.0F};
    float cameraTouchLastX_{0.0F};
    bool cameraTouchIsButton_{false};
    Aldrathar::DragonEntity dragon_{};
    bool isInsideHouse_{false};
};
