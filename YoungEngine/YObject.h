#pragma once
class YObject {
public:
    YObject() = default;
    virtual ~YObject() = default;

    virtual void Update(float deltaTime) {}

    virtual void Draw() {}
};