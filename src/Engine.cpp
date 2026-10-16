#include "Engine.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <algorithm>
#include <iostream>
#include <string>

Engine::Engine()
    : m_window(
          sf::VideoMode({960u, 720u}),
          "Aldrathar"
      ),
      m_renderTexture({320u, 240u}),
      m_screenSprite(m_renderTexture.getTexture())
{
    m_window.setVerticalSyncEnabled(true);

    m_renderTexture.setSmooth(false);

    m_screenSprite.setScale({
        3.0F,
        3.0F
    });

    const std::string shaderPath =
        std::string(ALDRATHAR_SHADER_DIR) + "/retro.frag";

    if (!m_retroShader.loadFromFile(
            shaderPath,
            sf::Shader::Type::Fragment
        ))
    {
        std::cerr
            << "ERROR: No se pudo cargar shader: "
            << shaderPath
            << '\n';
    }
}

void Engine::run()
{
    sf::Clock clock;

    while (m_window.isOpen()) {

        const float deltaTime =
            std::min(clock.restart().asSeconds(), 0.25F);

        processEvents();

        m_accumulator += deltaTime;

        while (m_accumulator >= FIXED_TIMESTEP) {
            update(FIXED_TIMESTEP);

            m_accumulator -= FIXED_TIMESTEP;
        }

        const float interpolation =
            m_accumulator / FIXED_TIMESTEP;

        render(interpolation);
    }
}

void Engine::processEvents()
{
    while (const std::optional event = m_window.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

void Engine::update(float fixedDeltaTime)
{
    (void)fixedDeltaTime;
}

void Engine::render(float interpolation)
{
    (void)interpolation;

    // --------------------------------------------------------
    // Render interno: 320x240
    // --------------------------------------------------------

    m_renderTexture.clear(sf::Color::Black);

    sf::RectangleShape rectangle({
        100.0F,
        60.0F
    });

    rectangle.setPosition({
        110.0F,
        90.0F
    });

    rectangle.setFillColor(
        sf::Color(0, 255, 0)
    );

    m_renderTexture.draw(rectangle);

    m_renderTexture.display();

    // --------------------------------------------------------
    // Render final + shader
    // --------------------------------------------------------

    m_window.clear(sf::Color::Black);

    m_window.draw(
        m_screenSprite,
        &m_retroShader
    );

    m_window.display();
}
