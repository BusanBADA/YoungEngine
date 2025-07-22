#pragma once
#include <SDL3/SDL.h>

class RendererManager {
public:
    bool Init(SDL_Window* window);
    void Destroy();
    SDL_Renderer* GetRenderer() const { return m_renderer; }
private:
    SDL_Renderer* m_renderer = nullptr;
};
