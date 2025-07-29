#include <SDL3/SDL.h>
#include "YoungEngine.h"
#include <iostream>
#include "Config.h"
#include <memory>
#include "GameState.h"
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

    Uint32 flags = SDL_WINDOW_OPENGL;
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
            m_windowManager.ProcessEvent(event);
            m_inputManager.ProcessEvent(event);
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
    m_rendererManager.BeginFrame();
    m_rendererManager.DrawObjects(m_objectManager.GetAllDrawableObjects());
    m_rendererManager.EndFrame();
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

void Engine::SetGameState(std::shared_ptr<class GameState> newState)
{
    m_objectManager.RemoveAllObjects();
    m_currentState = newState;
    newState->SetInput(&m_inputManager);
    if (m_currentState) {
        m_currentState->Init();
    }
    m_objectManager.AddObject(m_currentState);
    m_objectManager.AddObjects(newState->GetAllObjects());
    
}
