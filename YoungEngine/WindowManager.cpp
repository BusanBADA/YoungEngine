#include "WindowManager.h"
#include <glad/glad.h>
bool WindowManager::Init(const char* title, int width, int height, Uint32 flags) {
    m_window = SDL_CreateWindow(title, width, height, flags);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6); 
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