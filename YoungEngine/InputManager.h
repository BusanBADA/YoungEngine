#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include "InputInterface.h"

class InputManager : public InputInterface {
public:
    void ProcessEvent(const SDL_Event& event);

    bool IsKeyPressed(KeyInput key) const;

    void Clear();

private:
    std::unordered_map<KeyInput, bool> m_keyStates;
};