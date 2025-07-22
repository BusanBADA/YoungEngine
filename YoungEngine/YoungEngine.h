#pragma once
#include <windows.h>

namespace YoungEngine {

    using InitFunc = void(*)();
    using UpdateFunc = void(*)(float);

    class engine {
    public:
        static InitFunc userInit;
        static UpdateFunc userUpdate;
        HWND m_hwnd;
        void run();
        void init(HWND hwnd);
        void update();
        void render();
    };

    // 등록 매크로
#define REGISTER_GAME(INIT_FN, UPDATE_FN) \
        namespace YoungEngine { \
            InitFunc userInit = INIT_FN; \
            UpdateFunc userUpdate = UPDATE_FN; \
        }

}