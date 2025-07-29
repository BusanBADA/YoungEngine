#pragma once
#include "Object.h"
#include "InputInterface.h"
#include <memory>
#include <vector>
class GameState : public Object
{
public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	std::vector<std::shared_ptr<Object>>GetAllObjects();
	void SetInput(InputInterface* input);
protected:
	std::vector<std::shared_ptr<Object>> m_objects;
	InputInterface* m_inputInterface = nullptr;
};