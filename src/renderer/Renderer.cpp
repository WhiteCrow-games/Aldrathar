#include "renderer/Renderer.hpp"

#include <iostream>
#include <string>

#ifndef ALDRATHAR_SHADER_DIR
#define ALDRATHAR_SHADER_DIR "assets/shaders"
#endif

Renderer::~Renderer()
{
    shutdown();
}

bool Renderer::initialize(int windowWidth, int windowHeight)
{
    windowWidth_ = windowWidth;
    windowHeight_ = windowHeight;

    target_ = LoadRenderTexture(INTERNAL_WIDTH, INTERNAL_HEIGHT);
    targetReady_ = target_.id != 0;

    if (!targetReady_) {
        std::cerr << "ERROR: No se pudo crear RenderTexture2D.\n";
        return false;
    }

    SetTextureFilter(target_.texture, TEXTURE_FILTER_POINT);

    const std::string shaderPath =
        std::string(ALDRATHAR_SHADER_DIR) + "/retro.frag";

    retroShader_ = LoadShader(nullptr, shaderPath.c_str());
    shaderReady_ = retroShader_.id != 0;

    if (!shaderReady_) {
        std::cerr
            << "AVISO: Shader retro no disponible; se usara renderizado normal.\n";
    }

    return true;
}

void Renderer::shutdown()
{
    if (shaderReady_) {
        UnloadShader(retroShader_);
        shaderReady_ = false;
    }

    if (targetReady_) {
        UnloadRenderTexture(target_);
        targetReady_ = false;
    }
}

void Renderer::beginScene()
{
    BeginTextureMode(target_);
    ClearBackground(Color{12, 14, 22, 255});
}

void Renderer::endScene()
{
    EndTextureMode();
}

void Renderer::present()
{
    BeginDrawing();
    ClearBackground(BLACK);

    const Rectangle source{
        0.0F,
        0.0F,
        static_cast<float>(INTERNAL_WIDTH),
        -static_cast<float>(INTERNAL_HEIGHT)
    };

    const Rectangle destination{
        0.0F,
        0.0F,
        static_cast<float>(windowWidth_),
        static_cast<float>(windowHeight_)
    };

    if (shaderReady_)
        BeginShaderMode(retroShader_);

    DrawTexturePro(
        target_.texture,
        source,
        destination,
        Vector2{0.0F, 0.0F},
        0.0F,
        WHITE
    );

    if (shaderReady_)
        EndShaderMode();

    EndDrawing();
}
