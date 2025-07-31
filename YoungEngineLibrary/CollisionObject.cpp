#include "CollisionObject.h"
#include <glm/glm.hpp>
#include <algorithm>
void CollisionObject::Update(float deltaTime) {
    DrawableObject::Update(deltaTime);

}
void CollisionObject::SetCollisionType(CollisionType type)
{ 
    collisionType = type;
}
CollisionType CollisionObject::GetCollisionType() const 
{ 
    return collisionType;
}
bool CollisionObject::CheckCollision(CollisionObject& other)
{
    if (this->GetCollisionType()==CollisionType::NOCOLLISION || other.GetCollisionType() == CollisionType::NOCOLLISION)
        return false;

    CollisionType typeA = this->GetCollisionType();
    CollisionType typeB = other.GetCollisionType();

    if (typeA == AABB && typeB == AABB)
        return CheckAABBCollision(other);
    else if (typeA == RADIUS && typeB == RADIUS)
        return CheckRadiusCollision(other);
    else if (typeA == ELLIPSE && typeB == ELLIPSE)
        return CheckEllipseCollision(other);
    else if (typeA == AABB && typeB == RADIUS)
        return CheckAABBCircleCollision(*this, other);
    else if (typeA == RADIUS && typeB == AABB)
        return CheckAABBCircleCollision(other, *this);
    else if (typeA == ELLIPSE && typeB == RADIUS)
        return CheckEllipseCircleCollision(*this, other);
    else if (typeA == RADIUS && typeB == ELLIPSE)
        return CheckEllipseCircleCollision(other, *this);
    else if (typeA == ELLIPSE && typeB == AABB)
        return CheckEllipseAABBCollision(*this, other);
    else if (typeA == AABB && typeB == ELLIPSE)
        return CheckEllipseAABBCollision(other, *this);


    return false;
}
void CollisionObject::SetOnCollision(std::function<void(CollisionObject&)> callback) {
    onCollision = callback;
}
bool CollisionObject::HasCollisionCallback() const 
{ 
    return static_cast<bool>(onCollision);
}
void CollisionObject::OnCollision(CollisionObject& other) 
{ 
    if (onCollision)
    {
        onCollision(other);
    }
}

bool CollisionObject::CheckAABBCollision(CollisionObject& other)
{
    SDL_FRect* a = GetRect();
    SDL_FRect* b = other.GetRect();

    return a->x < b->x + b->w &&
        a->x + a->w > b->x &&
        a->y < b->y + b->h &&
        a->y + a->h > b->y;
}

bool CollisionObject::CheckRadiusCollision(CollisionObject& other)
{
    glm::vec2 centerA = { GetRect()->x + GetRect()->w / 2.0f, GetRect()->y + GetRect()->h / 2.0f };
    glm::vec2 centerB = { other.GetRect()->x + other.GetRect()->w / 2.0f, other.GetRect()->y + other.GetRect()->h / 2.0f };

    float radiusA = std::min(GetRect()->w, GetRect()->h) / 2.0f;
    float radiusB = std::min(other.GetRect()->w, other.GetRect()->h) / 2.0f;

    float distSq = glm::distance(centerA, centerB);
    float radiusSum = radiusA + radiusB;

    return distSq <= radiusSum * radiusSum;
}

bool CollisionObject::CheckEllipseCollision(CollisionObject& other)
{
    glm::vec2 centerA = { GetRect()->x + GetRect()->w / 2.0f, GetRect()->y + GetRect()->h / 2.0f };
    glm::vec2 centerB = { other.GetRect()->x + other.GetRect()->w / 2.0f, other.GetRect()->y + other.GetRect()->h / 2.0f };

    glm::vec2 dist = centerB - centerA;

    float normX = dist.x / ((GetRect()->w + other.GetRect()->w) / 2.0f);
    float normY = dist.y / ((GetRect()->h + other.GetRect()->h) / 2.0f);

    float ellDist = normX * normX + normY * normY;

    return ellDist <= 1.0f;
}

bool CollisionObject::CheckAABBCircleCollision(CollisionObject& boxObj, CollisionObject& circleObj)
{
    const SDL_FRect* rect = boxObj.GetRect();
    const SDL_FRect* circ = circleObj.GetRect();

    glm::vec2 circleCenter = { circ->x + circ->w / 2.0f, circ->y + circ->h / 2.0f };
    float radius = std::min(circ->w, circ->h) / 2.0f;

    float closestX = std::clamp(circleCenter.x, rect->x, rect->x + rect->w);
    float closestY = std::clamp(circleCenter.y, rect->y, rect->y + rect->h);

    float dx = circleCenter.x - closestX;
    float dy = circleCenter.y - closestY;

    return (dx * dx + dy * dy) <= (radius * radius);
}

bool CollisionObject::CheckEllipseCircleCollision(CollisionObject& ellipseObj, CollisionObject& circleObj)
{
    SDL_FRect* ellipse = ellipseObj.GetRect();
    SDL_FRect* circle = circleObj.GetRect();

    glm::vec2 ellipseCenter = { ellipse->x + ellipse->w / 2.0f, ellipse->y + ellipse->h / 2.0f };
    glm::vec2 circleCenter = { circle->x + circle->w / 2.0f, circle->y + circle->h / 2.0f };

    float rx = ellipse->w / 2.0f + std::min(circle->w, circle->h) / 2.0f; // 타원 반지름 + 원 반지름
    float ry = ellipse->h / 2.0f + std::min(circle->w, circle->h) / 2.0f;

    float dx = circleCenter.x - ellipseCenter.x;
    float dy = circleCenter.y - ellipseCenter.y;

    float normalized = (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry);
    return normalized <= 1.0f;
}

bool CollisionObject::CheckEllipseAABBCollision(CollisionObject& ellipseObj, CollisionObject& aabbObj)
{
    SDL_FRect* ellipse = ellipseObj.GetRect();
    SDL_FRect* rect = aabbObj.GetRect();

    glm::vec2 ellipseCenter = { ellipse->x + ellipse->w / 2.0f, ellipse->y + ellipse->h / 2.0f };
    glm::vec2 rectCenter = { rect->x + rect->w / 2.0f, rect->y + rect->h / 2.0f };

    float rx = ellipse->w / 2.0f + rect->w / 2.0f;
    float ry = ellipse->h / 2.0f + rect->h / 2.0f;

    float dx = rectCenter.x - ellipseCenter.x;
    float dy = rectCenter.y - ellipseCenter.y;

    float normalized = (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry);
    return normalized <= 1.0f;
}