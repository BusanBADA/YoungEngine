#include "ObjectManager.h"
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

void ObjectManager::RemoveObject(Object* objPtr)
{
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
        [&](const std::shared_ptr<Object>& o) { return o.get() == objPtr; }),
        m_objects.end());
}
