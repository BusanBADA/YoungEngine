#pragma once
#include "DrawableObject.h"
#include <functional>

enum CollisionType
{
    NOCOLLISION,
    AABB,
    RADIUS,
    ELLIPSE,
};

class CollisionObject : public DrawableObject
{
public:
    virtual void Update(float deltaTime) override;

    void SetCollisionType(CollisionType type);
    CollisionType GetCollisionType() const;
    bool CheckCollision(CollisionObject& other);

    void SetOnCollision(std::function<void(CollisionObject&)> callback);

    bool HasCollisionCallback() const;
    void OnCollision(CollisionObject& other);
    bool CheckAABBCollision(CollisionObject& other);
    bool CheckRadiusCollision(CollisionObject& other);
    bool CheckEllipseCollision(CollisionObject& other);
    bool CheckAABBCircleCollision(CollisionObject& boxObj, CollisionObject& circleObj);
    bool CheckEllipseCircleCollision(CollisionObject& ellipseObj, CollisionObject& circleObj);
    bool CheckEllipseAABBCollision(CollisionObject& ellipseObj, CollisionObject& aabbObj);
protected:

private:
    std::function<void(CollisionObject&)> onCollision = nullptr;
    CollisionType collisionType = CollisionType::NOCOLLISION;
};