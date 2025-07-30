#include "Game.h"
#include <iostream>
void Game::Init()
{
    GameState::Init();

    std::shared_ptr<Box> Ptr = std::make_shared<Box>();
    Ptr->SetRect(100.f, 100.f, 200.f, 200.f);
    Ptr->SetColor(255.f, 255.f, 255.f, 255.f);
    Ptr->SetInput(m_inputInterface);

    GLuint texID = m_renderInterface->LoadTexture("Assets/spritesheet2.png");
    Ptr->SetTexture(texID);

    Ptr->SetUV(0, 4, 5);
    Ptr->SetUsingIndexes({ 0, 1, 2, 3, 4, 5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
    m_objects.push_back(Ptr);
}

void Game::Update(float deltaTime)
{
	GameState::Update(deltaTime);
}

void Box::Update(float deltaTime)
{
    DrawableObject::Update(deltaTime);
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
        rect->y += speed * deltaTime;
    }
    if (m_inputInterface->IsKeyPressed(KEY_DOWN)) {
        rect->y -= speed * deltaTime;
    }

    if (m_inputInterface->IsMouseButtonPressed(MOUSE_LEFT)) {
        int mx, my;
        m_inputInterface->GetMousePosition(mx, my);
        std::cout << "Left click at: " << mx << ", " << my << "\n";
    }

    SetRect(rect->x, rect->y, rect->w, rect->h);
}