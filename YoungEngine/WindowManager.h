#pragma once
#include <SDL3/SDL.h>

class WindowManager {
public:
    bool Init(const char* title, int width, int height, Uint32 flags);
    void Destroy();
    SDL_Window* GetWindow() const { return m_window; }
    bool ProcessEvent(const SDL_Event& event);
private:
    SDL_Window* m_window = nullptr;
};

