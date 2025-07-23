#pragma once
#include <SDL3/SDL.h>
class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    SDL_FRect GetRect() const { return rect; }
    SDL_Color GetColor() const { return color; }
    void SetRect(const SDL_FRect& r) { rect = r; }
    void SetColor(const SDL_Color& c) { color = c; }
    virtual void Update(float deltaTime) {}
private:
    SDL_FRect rect;
    SDL_Color color;
};