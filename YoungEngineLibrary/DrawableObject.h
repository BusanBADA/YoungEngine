#pragma once
#include "Object.h"

class DrawableObject : public Object
{
public:
	virtual void Update(float deltaTime) override;
	SDL_FRect* GetRect();
	SDL_Color* GetColor();
private:
	SDL_FRect Rect;
	SDL_Color Color;
};