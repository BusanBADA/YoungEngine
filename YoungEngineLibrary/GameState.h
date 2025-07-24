#pragma once
#include "Object.h"

class GameState : public Object
{
public:
	virtual void Update(float deltaTime) override;
};