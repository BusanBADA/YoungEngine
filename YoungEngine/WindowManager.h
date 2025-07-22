#pragma once
#include <SDL3/SDL.h>

class WindowManager {
public:
    bool Init(const char* title, int width, int height);
    void Destroy();
    SDL_Window* GetWindow() const { return m_window; }
private:
    SDL_Window* m_window = nullptr;
};

