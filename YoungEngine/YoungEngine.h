#pragma once
#include "ObjectManager.h"
#include "WindowManager.h"
#include "RenderManager.h"

class Engine {
public:
    Engine() = default;

    void Run();

    bool Init();
    void Update(float deltaTime);
    void Render();
    void Shutdown();

    void Temp();
        
    void AddObject(std::shared_ptr<Object> object);
        
private:
    bool m_running = false;
    ObjectManager m_objectManager;
    WindowManager m_windowManager;
    RendererManager m_rendererManager;

    Uint64 m_previousCounter = 0;
    double m_frequency = 0.0;
};
