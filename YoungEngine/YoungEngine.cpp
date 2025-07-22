#include "YoungEngine.h"
#include <iostream>

namespace YoungEngine {

    InitFunc engine::userInit = nullptr;
    UpdateFunc engine::userUpdate = nullptr;

    void engine::init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        m_window = SDL_CreateWindow("YoungEngine SDL3 Window", 800, 600, SDL_WINDOW_RESIZABLE);
        if (!m_window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        SDL_ShowWindow(m_window);

        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return;
        }

        if (userInit) userInit();
        m_running = true;
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

        // Á¤¸®
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

        SDL_FRect rect = { 50.0f, 50.0f, 200.0f, 100.0f };  // SDL3´Â float ÁÂÇ¥
        SDL_RenderFillRect(m_renderer, &rect);

        SDL_RenderPresent(m_renderer);
    }
}