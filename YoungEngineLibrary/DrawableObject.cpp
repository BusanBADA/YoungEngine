#include "DrawableObject.h"

void DrawableObject::Update(float deltaTime)
{
	Object::Update(deltaTime);
}
void DrawableObject::SetRect(float x, float y, float w, float h)
{
	Rect.x = x;
	Rect.y = y;
	Rect.w = w;
	Rect.h = h;
}
SDL_FRect* DrawableObject::GetRect()
{
	return &Rect;
}
void DrawableObject::SetColor(float r, float g, float b, float a)
{
	Color.r = r;
	Color.g = g;
	Color.b = b;
	Color.a = a;
}
SDL_Color* DrawableObject::GetColor()
{
	return &Color;
}