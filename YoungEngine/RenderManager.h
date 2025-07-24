#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "DrawableObject.h"
class RendererManager {
public:
    bool Init(SDL_Window* window);
    void BeginFrame(); // SDL_RenderClear µî
    void EndFrame();   // SDL_RenderPresent µî
    void DrawObjects(const std::vector<std::shared_ptr<DrawableObject>>& objects);
    void DrawRect(const SDL_FRect& rect, const SDL_Color& color);
    void Destroy();
    SDL_Renderer* GetRenderer() const { return m_renderer; }
private:
    SDL_Renderer* m_renderer = nullptr;
};
