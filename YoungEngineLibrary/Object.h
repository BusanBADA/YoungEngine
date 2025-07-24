#pragma once
#include <SDL3/SDL.h>
class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    virtual void Update(float deltaTime) {}
};