#pragma once
#include <string>
#include <glad/glad.h>
class RenderInterface {
public:
    virtual ~RenderInterface() = default;
    virtual GLuint LoadTexture(const char* path) = 0;
};