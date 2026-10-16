#pragma once

#include <raylib.h>

class Game {
public:
    void initialize();
    void update(float fixedDeltaTime);
    void render(float interpolation);

private:
    void drawRoom();
    void drawFurniture();

    Camera3D camera_{};
    float elapsedTime_ = 0.0F;
};
