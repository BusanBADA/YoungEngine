#include "ObjectManager.h"
#include "DrawableObject.h"
#include <memory>


ObjectManager& ObjectManager::GetInstance()
{
    static ObjectManager instance;
    return instance;
}

void ObjectManager::AddObject(std::shared_ptr<Object> obj)
{
    m_objects.push_back(obj);
}

void ObjectManager::AddObjects(std::vector<std::shared_ptr<Object>> objs)
{
    for (std::shared_ptr<Object>obj : objs)
    {
        m_objects.push_back(obj);
    }
}
void ObjectManager::SetObjects(std::vector<std::shared_ptr<Object>> objs)
{
    RemoveAllObjects();
    m_objects = objs;
}
void ObjectManager::UpdateAll(float deltaTime)
{
    for (auto& obj : m_objects) {
        obj->Update(deltaTime);
    }
}

const std::vector<std::shared_ptr<Object>> ObjectManager::GetAllObjects() const
{
    return m_objects;
}

const std::vector<std::shared_ptr<DrawableObject>> ObjectManager::GetAllDrawableObjects() const
{
    std::vector<std::shared_ptr<DrawableObject>> result;
    for (auto& obj : m_objects) {
        auto drawable = std::dynamic_pointer_cast<DrawableObject>(obj);
        if (drawable) {
            result.push_back(drawable);
        }
    }
    return result;
}

void ObjectManager::RemoveObject(Object* objPtr)
{
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
        [&](const std::shared_ptr<Object>& o) { return o.get() == objPtr; }),
        m_objects.end());
}

void ObjectManager::RemoveAllObjects()
{
    m_objects.clear();
}
