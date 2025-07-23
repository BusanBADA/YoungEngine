#include "YoungEngine.h"
#include "Game.h"
#include "Object.h"
#include<memory>
static float x = 100.0f;
static float speed = 100.0f; // px per second


void GameInit(Engine* InEngine) {
    std::shared_ptr<Box> redBox = std::make_shared<Box>();

    // Object�� �����ڳ� setter�� ���ٸ� ���� ������� ���� �����ϵ��� �Լ� �߰� �ʿ�
    // ���� ��� Object�� SetRect, SetColor �Լ� ������ ��
    redBox->SetRect({ 100.0f, 100.0f, 150.0f, 100.0f });
    redBox->SetColor({ 255, 0, 0, 255 });
    
    //InEngine->Temp();//AddObject(redBox);
}

void GameUpdate(float dt) {
    
}