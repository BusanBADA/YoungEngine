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
    // �ʿ�� ��� ������ �߰�
};
class Box : public Object
{
    
};
void GameInit();
void GameUpdate(float dt);