#pragma once
#include "Object.h"
#include <memory>
#include <vector>

class ObjectManager {
public:

    ObjectManager() = default;
    static ObjectManager& GetInstance();

    void AddObject(std::shared_ptr<Object> obj);

    void UpdateAll(float deltaTime);

    void RemoveObject(Object* objPtr);

private:
    std::vector<std::shared_ptr<Object>> objects;
};