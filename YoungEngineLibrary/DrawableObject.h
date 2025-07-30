#pragma once
#include "Object.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
class DrawableObject : public Object
{
public:
	virtual void Update(float deltaTime) override;
	void SetRect(float x, float y, float w, float h);
	SDL_FRect* GetRect();
	void SetColor(float r, float g, float b, float a);
	SDL_Color* GetColor();
	void SetTexture(GLuint texID) { textureID = texID; }
	GLuint GetTexture() const { return textureID; }

	void SetUV(int frame, int cols, int rows);
	glm::vec2 GetTexOffset() const;
	glm::vec2 GetTexScale() const;

	void SetUsingIndexes(std::vector<int> NewIndexes);
	void ClearUsingIndexes();

protected:
	int m_currentFrame = 1;
	int m_totalFrames = 1;
	int m_frameCols = 1;
	int m_frameRows = 1;

	float m_frameTimer = 0.0f;
	float m_frameDuration = 0.1f;

	
private:
	SDL_FRect rect;
	SDL_Color color;
	GLuint textureID = 0;

	glm::vec2 texOffset = { 0.0f, 0.0f };
	glm::vec2 texScale = { 1.0f, 1.0f };

	bool m_useTotalFrame = true;
	std::vector<int> UsingIndexes;
	size_t m_currentIndexInUsing = 0;
};