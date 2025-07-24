#include "RenderManager.h"

bool RendererManager::Init(SDL_Window* window) {
    m_renderer = SDL_CreateRenderer(window, nullptr);
    return (m_renderer != nullptr);
}
void RendererManager::BeginFrame()
{
}
void RendererManager::EndFrame()
{
}
void RendererManager::DrawObjects(const std::vector<std::shared_ptr<DrawableObject>>& objects)
{
    for (const std::shared_ptr<DrawableObject>& obj : objects)
    {
        SDL_FRect* rect = obj->GetRect();
        SDL_Color* color = obj->GetColor();

        SDL_SetRenderDrawColor(m_renderer, color->r, color->g, color->b, color->a);
        SDL_RenderFillRect(m_renderer, rect);
    }
}
void RendererManager::DrawRect(const SDL_FRect& rect, const SDL_Color& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &rect);
}
void RendererManager::Destroy() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}