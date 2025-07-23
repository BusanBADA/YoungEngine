#include <SDL3/SDL.h>
#include "YoungEngine.h"
#include <iostream>
#include "Config.h"
#include <memory>

bool Engine::Init() {
    Config config;
    if (!config.LoadFromFile("Settings.ini")) {
        std::cerr << "Failed to load Setting.ini, using default values\n";
    }

    std::string title = config.GetString("Window.Title", "Default Window");
    int width = config.GetInt("Window.Width", 800);
    int height = config.GetInt("Window.Height", 600);
    bool resizable = config.GetBool("Window.Resizable", true);
    bool fullscreen = config.GetBool("Graphics.Fullscreen", true);

    Uint32 flags = 0;
    if (resizable) flags |= SDL_WINDOW_RESIZABLE;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!m_windowManager.Init(title.c_str(), width, height, flags)) {
        std::cerr << "Window Init failed" << std::endl;
        SDL_Quit();
        return false;
    }

    if (!m_rendererManager.Init(m_windowManager.GetWindow())) {
        std::cerr << "Renderer Init failed" << std::endl;
        m_windowManager.Destroy();
        SDL_Quit();
        return false;
    }
    SDL_ShowWindow(m_windowManager.GetWindow());
    m_running = true;
    m_frequency = (double)SDL_GetPerformanceFrequency();
    m_previousCounter = SDL_GetPerformanceCounter();
    return true;
}


void Engine::Run() {
    Init();

    SDL_Event event;
    const float deltaTime = 1.0f / 60.0f;

    while (m_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }
        }

        Uint64 currentCounter = SDL_GetPerformanceCounter();

        // deltaTime 초 단위 계산
        float deltaTime = (float)((currentCounter - m_previousCounter) / m_frequency);

        m_previousCounter = currentCounter;


        Update(deltaTime);
        Render();
    }
    SDL_Quit();
}

void Engine::Update(float deltaTime) {
    m_objectManager.UpdateAll(deltaTime);
}

void Engine::Render() {
    SDL_Renderer* renderer = m_rendererManager.GetRenderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    m_rendererManager.DrawObjects(m_objectManager.GetAllObjects());

    SDL_RenderPresent(renderer);
}
   
void Engine::Shutdown()
{
    m_rendererManager.Destroy();
    m_windowManager.Destroy();
    SDL_Quit();
} 
void Engine::AddObject(std::shared_ptr<Object> object)
{
    m_objectManager.AddObject(object);
}

void Engine::Temp()
{

}