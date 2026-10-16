#pragma once

#include "game/Game.hpp"
#include "renderer/Renderer.hpp"

class Engine {
public:
    Engine() = default;
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    bool initialize();
    void run();

private:
    void processEvents();
    void update(float fixedDeltaTime);
    void render(float interpolation);

    static constexpr int WINDOW_WIDTH = 960;
    static constexpr int WINDOW_HEIGHT = 720;
    static constexpr float FIXED_TIMESTEP = 1.0F / 60.0F;

    float accumulator_ = 0.0F;
    bool initialized_ = false;

    Renderer renderer_;
    Game game_;
};
