#include "InputManager.h"

void InputManager::ProcessEvent(const SDL_Event& event)
{
    KeyInput Input = ToKeyInput(event.key.scancode);
    if (event.type == SDL_EVENT_KEY_DOWN) {
        m_keyStates[Input] = true;
    }
    else if (event.type == SDL_EVENT_KEY_UP) {
        m_keyStates[Input] = false;
    }
}

bool InputManager::IsKeyPressed(KeyInput key) const
{
    auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && it->second;
}

void InputManager::Clear()
{
    m_keyStates.clear();
}
