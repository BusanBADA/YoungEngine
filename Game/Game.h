#pragma once

#include <memory>
#include "Object.h"

class Game
{
public:
    Game() = default;
    void Init();
    void Update(float deltaTime);

private:
    // 필요시 멤버 변수들 추가
};
class Box : public Object
{
    
};
void GameInit();
void GameUpdate(float dt);