#pragma once
#include "Object.h"
#include <memory>
#include <vector>

class ObjectManager {
public:

    ObjectManager() = default;
    static ObjectManager& GetInstance();

    void AddObject(std::shared_ptr<Object> obj);
    void AddObjects(std::vector<std::shared_ptr<Object>> objs);
    void SetObjects(std::vector<std::shared_ptr<Object>> objs);
    void UpdateAll(float deltaTime);
    const std::vector<std::shared_ptr<Object>> GetAllObjects() const;
    const std::vector<std::shared_ptr<class DrawableObject>> GetAllDrawableObjects() const;
    void RemoveObject(Object* objPtr);
    void RemoveAllObjects();
private:
    std::vector<std::shared_ptr<Object>> m_objects;
};