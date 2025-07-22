#include "YoungEngine.h"
#include <iostream>
#include "Config.h"

namespace YoungEngine {

    InitFunc engine::userInit = nullptr;
    UpdateFunc engine::userUpdate = nullptr;

    bool engine::init() {
        Config config;
        if (!config.LoadFromFile("Settings.ini")) {
            std::cerr << "Failed to load Setting.ini, using default values\n";
        }

        std::string title = config.GetString("Window.Title", "Default Window");
        int width = config.GetInt("Window.Width", 800);
        int height = config.GetInt("Window.Height", 600);
        bool resizable = config.GetBool("Window.Resizable", true);

        Uint32 flags = 0;
        if (resizable) flags |= SDL_WINDOW_RESIZABLE;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!m_windowManager.Init(title.c_str(), width, height)) {
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

        if (userInit) userInit();

        return true;
    }


    void engine::run() {
        init();

        SDL_Event event;
        const float deltaTime = 1.0f / 60.0f;

        while (m_running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    m_running = false;
                }
            }

            if (userUpdate) userUpdate(deltaTime);

            render();
            SDL_Delay(16);
        }

        if (m_renderer) SDL_DestroyRenderer(m_renderer);
        if (m_window) SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void engine::update() {
    }

    void engine::render() {
        if (!m_renderer) return;

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);

        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

        SDL_FRect rect = { 50.0f, 50.0f, 200.0f, 100.0f };
        SDL_RenderFillRect(m_renderer, &rect);

        SDL_RenderPresent(m_renderer);
    }

    void engine::Shutdown()
    {
        m_rendererManager.Destroy();
        m_windowManager.Destroy();
        SDL_Quit();
    }
}
