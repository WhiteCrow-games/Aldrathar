#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include "game/Player.hpp"

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
    void drawDragon();
    void drawRoom();
    void drawFurniture();
    Camera3D camera_{};
    Aldrathar::Player player_{};
    Aldrathar::Entity* playerEntity_{&player_};
    float elapsedTime_{0.0f};
    bool isometric_{false};
    Vector2 joystickCenter_{48.0f, 192.0f};
    Vector2 joystickKnob_{48.0f, 192.0f};
    Vector2 touchMove_{0,0};
    int joystickTouchId_{-1};
    int cameraTouchId_{-1};
    bool cameraTouchWasDown_{false};
    Vector3 dragonPos_{0.0f, 0.0f, -8.5f};
    float dragonIdle_{0.0f};
    static constexpr float DRAGON_IDLE_SPEED = 15.0f;
    bool isInsideHouse_{false};
};
