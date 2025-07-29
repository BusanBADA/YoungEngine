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
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        MouseInput button;

        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            button = MOUSE_LEFT;
            break;
        case SDL_BUTTON_RIGHT:
            button = MOUSE_RIGHT;
            break;
        case SDL_BUTTON_MIDDLE:
            button = MOUSE_MIDDLE;
            break;
        default:
            return; // 지원하지 않는 마우스 버튼
        }

        m_mouseButtonStates[button] = (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
    }
    else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        m_mouseX = event.motion.x;
        m_mouseY = event.motion.y;
    }
}

bool InputManager::IsKeyPressed(KeyInput key) const
{
    auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && it->second;
}

bool InputManager::IsMouseButtonPressed(MouseInput button) const
{
    auto it = m_mouseButtonStates.find(button);
    return it != m_mouseButtonStates.end() && it->second;
}

void InputManager::GetMousePosition(int& x, int& y) const
{
    x = m_mouseX;
    y = m_mouseY;
}

void InputManager::Clear()
{
    m_keyStates.clear();
}
