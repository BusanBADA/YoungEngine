#include "WindowManager.h"
#include <glad/glad.h>
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

bool WindowManager::ProcessEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_WINDOW_RESIZED) {
        glViewport(0, 0, event.window.data1, event.window.data2);
        return true;
    }
    return false;
}