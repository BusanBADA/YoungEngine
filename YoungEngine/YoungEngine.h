#pragma once
#include <SDL3/SDL.h>
#include "YObjectManager.h"
#include "WindowManager.h"
#include "RenderManager.h"

namespace YoungEngine {

    using InitFunc = void(*)();
    using UpdateFunc = void(*)(float);

    class engine {
    public:
        engine() = default;
        static InitFunc userInit;
        static UpdateFunc userUpdate;

        void run();

        bool init();
        void update();
        void render();
        void Shutdown();

    private:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        bool m_running = false;
        YObjectManager ObjectManager;
        WindowManager m_windowManager;
        RendererManager m_rendererManager;
    };

#define REGISTER_GAME(INIT_FN, UPDATE_FN) \
        namespace YoungEngine { \
            InitFunc userInit = INIT_FN; \
            UpdateFunc userUpdate = UPDATE_FN; \
        }

}