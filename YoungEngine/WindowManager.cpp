#include "WindowManager.h"

bool WindowManager::Init(const char* title, int width, int height, Uint32 flags) {
    m_window = SDL_CreateWindow(title, width, height, flags);
    return (m_window != nullptr);
}

void WindowManager::Destroy() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}
