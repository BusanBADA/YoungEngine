#include "YoungEngine.h"
#include "Game.h"
#include "Object.h"
#include<memory>
static float x = 100.0f;
static float speed = 100.0f; // px per second


void GameInit(Engine* InEngine) {
    std::shared_ptr<Box> redBox = std::make_shared<Box>();

    // Object의 생성자나 setter가 없다면 직접 멤버변수 접근 가능하도록 함수 추가 필요
    // 예를 들어 Object에 SetRect, SetColor 함수 만들어야 함
    redBox->SetRect({ 100.0f, 100.0f, 150.0f, 100.0f });
    redBox->SetColor({ 255, 0, 0, 255 });
    
    //InEngine->Temp();//AddObject(redBox);
}

void GameUpdate(float dt) {
    
}