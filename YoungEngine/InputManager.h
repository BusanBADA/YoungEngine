#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include "InputInterface.h"

class InputManager : public InputInterface {
public:
    void ProcessEvent(const SDL_Event& event);

    bool IsKeyPressed(KeyInput key) const;
    bool IsMouseButtonPressed(MouseInput button) const;
    void GetMousePosition(int& x, int& y) const;

    void Clear();

private:
    std::unordered_map<KeyInput, bool> m_keyStates;

    std::unordered_map<MouseInput, bool> m_mouseButtonStates;
    int m_mouseX = 0;
    int m_mouseY = 0;
};