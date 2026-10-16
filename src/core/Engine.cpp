#include "core/Engine.hpp"

#include <algorithm>
#include <iostream>

#include <raylib.h>

Engine::~Engine()
{
    renderer_.shutdown();

    if (initialized_)
        CloseWindow();
}

bool Engine::initialize()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Aldrathar");

    if (!IsWindowReady()) {
        std::cerr << "ERROR: No se pudo inicializar la ventana.\n";
        return false;
    }

    initialized_ = true;
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    if (!renderer_.initialize(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "ERROR: No se pudo inicializar Renderer.\n";
        return false;
    }

    game_.initialize();

    std::cout << "Aldrathar iniciado correctamente.\n";
    return true;
}

void Engine::run()
{
    if (!initialized_)
        return;

    while (!WindowShouldClose()) {
        processEvents();

        const float frameTime =
            std::min(GetFrameTime(), 0.25F);

        accumulator_ += frameTime;

        while (accumulator_ >= FIXED_TIMESTEP) {
            update(FIXED_TIMESTEP);
            accumulator_ -= FIXED_TIMESTEP;
        }

        const float interpolation =
            accumulator_ / FIXED_TIMESTEP;

        render(interpolation);
    }
}

void Engine::processEvents()
{
    // raylib procesa los eventos internamente.
    // WindowShouldClose() controla la salida del bucle.
}

void Engine::update(float fixedDeltaTime)
{
    game_.update(fixedDeltaTime);
}

void Engine::render(float interpolation)
{
    renderer_.beginScene();
    game_.render(interpolation);
    renderer_.endScene();
    renderer_.present();
}
