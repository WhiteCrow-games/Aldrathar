#pragma once

#include <SFML/Graphics.hpp>

class Engine {
public:
    Engine();
    ~Engine() = default;

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void run();

private:
    void processEvents();
    void update(float fixedDeltaTime);
    void render(float interpolation);

    sf::RenderWindow m_window;
    sf::RenderTexture m_renderTexture;
    sf::Sprite m_screenSprite;
    sf::Shader m_retroShader;

    static constexpr float FIXED_TIMESTEP = 1.0F / 60.0F;

    float m_accumulator = 0.0F;
};
