#pragma once
#include "Object.h"

class DrawableObject : public Object
{
public:
	virtual void Update(float deltaTime) override;
	void SetRect(float x, float y, float w, float h);
	SDL_FRect* GetRect();
	void SetColor(float r, float g, float b, float a);
	SDL_Color* GetColor();
private:
	SDL_FRect Rect;
	SDL_Color Color;
};