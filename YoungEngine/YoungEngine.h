#pragma once
#include <SDL3/SDL.h>

namespace YoungEngine {

    using InitFunc = void(*)();
    using UpdateFunc = void(*)(float);

    class engine {
    public:
        static InitFunc userInit;
        static UpdateFunc userUpdate;

        void run();

        void init();
        void update();
        void render();

    private:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        bool m_running = false;
    };

#define REGISTER_GAME(INIT_FN, UPDATE_FN) \
        namespace YoungEngine { \
            InitFunc userInit = INIT_FN; \
            UpdateFunc userUpdate = UPDATE_FN; \
        }

}