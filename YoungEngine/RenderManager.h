#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include "DrawableObject.h"
#include "RenderInterface.h"
class RendererManager : public RenderInterface
{
public:
    bool Init(SDL_Window* window);
    void BeginFrame(); // SDL_RenderClear µî
    void EndFrame();   // SDL_RenderPresent µî
    void DrawObjects(const std::vector<std::shared_ptr<DrawableObject>>& objects);
    virtual GLuint LoadTexture(const char* path) override;
    void Destroy();

private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;

    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_shaderProgram = 0;
};
