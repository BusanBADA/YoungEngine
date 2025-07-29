#include "GameState.h"

void GameState::Init()
{
	Object::Init();
}
void GameState::Update(float deltaTime)
{
	Object::Update(deltaTime);
}
std::vector<std::shared_ptr<Object>> GameState::GetAllObjects()
{
	return m_objects;
}
void GameState::SetInput(InputInterface* input)
{
	m_inputInterface = input;
}