#pragma once
#include "ObjectManager.h"
#include "WindowManager.h"
#include "RenderManager.h"
#include "InputManager.h"
class Engine {
public:
    Engine() = default;

    void Run();

    bool Init();
    void Update(float deltaTime);
    void Render();
    void Shutdown();
        
    void AddObject(std::shared_ptr<Object> object);
    void SetGameState(std::shared_ptr<class GameState> newState);
private:
    bool m_running = false;
    ObjectManager m_objectManager;
    WindowManager m_windowManager;
    RendererManager m_rendererManager;
    InputManager m_inputManager;

    Uint64 m_previousCounter = 0;
    double m_frequency = 0.0;

    std::shared_ptr<class GameState> m_currentState;
};
