#include "DrawableObject.h"

void DrawableObject::Update(float deltaTime)
{
	Object::Update(deltaTime);
}
SDL_FRect* DrawableObject::GetRect()
{
	return &Rect;
}
SDL_Color* DrawableObject::GetColor()
{
	return &Color;
}