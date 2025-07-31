#pragma once

#include <memory>
#include "CollisionObject.h"
#include "GameState.h"
class Game : public GameState
{
public:
    Game() = default;
    virtual void Init() override;
    virtual void Update(float deltaTime) override;

private:
};
class Box : public CollisionObject
{
public:
    virtual void Update(float deltaTime) override;

    void SetInput(InputInterface* input) {
        m_inputInterface = input;
    }

private:
    InputInterface* m_inputInterface = nullptr;
};
