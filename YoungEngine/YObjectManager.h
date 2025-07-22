#pragma once
#include "YObject.h"
#include <memory>
#include <vector>

class YObjectManager {
public:

    YObjectManager() = default;
    static YObjectManager& GetInstance();

    void AddObject(std::shared_ptr<YObject> obj);

    void UpdateAll(float deltaTime);

    void RemoveObject(YObject* objPtr);

private:
    std::vector<std::shared_ptr<YObject>> objects;
};