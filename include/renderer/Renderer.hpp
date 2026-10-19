#pragma once

#include <raylib.h>

class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool initialize(int windowWidth, int windowHeight);
    void shutdown();

    void beginScene();
    void endScene();
    void present();

    int internalWidth() const { return INTERNAL_WIDTH; }
    int internalHeight() const { return INTERNAL_HEIGHT; }

private:
    static constexpr int INTERNAL_WIDTH = 320;
    static constexpr int INTERNAL_HEIGHT = 240;

    RenderTexture2D target_{};
    Shader retroShader_{};
    int tiltShiftStrengthLoc_ = -1;

    int windowWidth_ = 0;
    int windowHeight_ = 0;

    bool targetReady_ = false;
    bool shaderReady_ = false;
};
