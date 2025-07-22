#include "RenderManager.h"

bool RendererManager::Init(SDL_Window* window) {
    m_renderer = SDL_CreateRenderer(window, nullptr);
    return (m_renderer != nullptr);
}

void RendererManager::Destroy() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}