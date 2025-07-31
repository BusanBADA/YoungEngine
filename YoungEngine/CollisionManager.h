#pragma once
#include <vector>
#include <memory>
#include "CollisionObject.h"

class CollisionManager {
public:
    void AddObject(std::shared_ptr<CollisionObject> obj);
    void AddObjects(std::vector<std::shared_ptr<CollisionObject>> objs);
    void SetObjects(std::vector<std::shared_ptr<CollisionObject>> objs);
    void RemoveAllObjects();
    void Update();

private:
    std::vector<std::shared_ptr<CollisionObject>> m_objects;
};