#include "YoungEngine.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace YoungEngine {

    InitFunc engine::userInit = nullptr;
    UpdateFunc engine::userUpdate = nullptr;

    void engine::run() {
        if (userInit) userInit();

        while (true) {
            if (userUpdate) userUpdate(0.016f); // 60fps
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    void engine::init(HWND hwnd) {
        m_hwnd = hwnd;
        
    }

    void engine::update() {
        
    }

    void engine::render() {
        HDC hdc = GetDC(m_hwnd);

        RECT rect;
        GetClientRect(m_hwnd, &rect);

        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // ¹è°æ Ä¥ÇÏ±â

        
        TextOut(hdc, 50, 50, L"Hello, YoungEngine!", 18);

        ReleaseDC(m_hwnd, hdc);
    }
}