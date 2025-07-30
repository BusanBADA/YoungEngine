#include "DrawableObject.h"
#include <iostream>
void DrawableObject::Update(float deltaTime)
{
	Object::Update(deltaTime);
	if (UsingIndexes.empty()) return;

	m_frameTimer += deltaTime;
	if (m_frameTimer >= m_frameDuration)
	{
		m_frameTimer = 0.0f;

		//1. 현재 인덱스의 프레임을 먼저 UV 설정
		int frame = UsingIndexes[m_currentIndexInUsing];
		std::cout << "frame: " << frame << " (index: " << m_currentIndexInUsing << ")\n";
		SetUV(frame, m_frameCols, m_frameRows);

		//2. 다음 인덱스로 넘어가기
		m_currentIndexInUsing++;
		if (m_currentIndexInUsing >= UsingIndexes.size()) {
			m_currentIndexInUsing = 0;
		}
	}
}
void DrawableObject::SetRect(float x, float y, float w, float h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}
SDL_FRect* DrawableObject::GetRect()
{
	return &rect;
}
void DrawableObject::SetColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}
SDL_Color* DrawableObject::GetColor()
{
	return &color;
}

void DrawableObject::SetUV(int frame, int cols, int rows)
{
	int col = frame % cols;
	int row = frame / cols;
	row = (rows - 1) - row;

	float uSize = 1.0f / cols;
	float vSize = 1.0f / rows;
	m_frameCols = cols;
	m_frameRows = rows;
	m_totalFrames = cols * rows;
	texOffset = glm::vec2(col * uSize, row * vSize);
	texScale = glm::vec2(uSize, vSize);
}
glm::vec2 DrawableObject::GetTexOffset() const
{ 
	return texOffset;
}
glm::vec2 DrawableObject::GetTexScale() const
{
	return texScale;
}

void DrawableObject::SetUsingIndexes(std::vector<int> NewIndexes)
{
	ClearUsingIndexes();
	UsingIndexes = NewIndexes;
	m_currentIndexInUsing = 0;
	if (!UsingIndexes.empty())
	{
		int firstFrame = UsingIndexes[0];
		SetUV(firstFrame, m_frameCols, m_frameRows); // 바로 첫 프레임 UV 설정
	}
}
void DrawableObject::ClearUsingIndexes()
{
	UsingIndexes.clear();
	m_currentFrame = 1;
	m_currentIndexInUsing = 0;
	SetUV(0, m_frameCols, m_frameRows);
}