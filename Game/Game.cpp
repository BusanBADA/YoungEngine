#include "Game.h"
#include <iostream>
void Game::Init()
{
	GameState::Init();
	std::shared_ptr<Box> Ptr = std::make_shared<Box>();
	Ptr->SetRect(100.f, 100.f, 200.f, 200.f);
	Ptr->SetColor(255.f, 1.f, 1.f, 255.f);
	Ptr->SetInput(m_inputInterface);  // input ¿¬°á
	m_objects.push_back(Ptr);
}

void Game::Update(float deltaTime)
{
	GameState::Update(deltaTime);
}

void Box::Update(float deltaTime)
{
    if (!m_inputInterface) return;

    float speed = 200.0f; // pixels per second
    SDL_FRect* rect = GetRect();

    if (m_inputInterface->IsKeyPressed(KEY_LEFT)) {
        rect->x -= speed * deltaTime;
    }
    if (m_inputInterface->IsKeyPressed(KEY_RIGHT)) {
        rect->x += speed * deltaTime;
    }
    if (m_inputInterface->IsKeyPressed(KEY_UP)) {
        rect->y -= speed * deltaTime;
    }
    if (m_inputInterface->IsKeyPressed(KEY_DOWN)) {
        rect->y += speed * deltaTime;
    }
    if (m_inputInterface->IsMouseButtonPressed(MOUSE_LEFT)) {
        int mx, my;
        m_inputInterface->GetMousePosition(mx, my);
        std::cout << "Left click at: " << mx << ", " << my << "\n";
    }
    SetRect(rect->x, rect->y, rect->w, rect->h);
}
