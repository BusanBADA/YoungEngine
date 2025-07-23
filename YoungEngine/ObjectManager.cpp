#include "ObjectManager.h"



ObjectManager& ObjectManager::GetInstance()
{
    static ObjectManager instance;
    return instance;
}

void ObjectManager::AddObject(std::shared_ptr<Object> obj)
{
    objects.push_back(obj);
}

void ObjectManager::UpdateAll(float deltaTime)
{
    for (auto& obj : objects) {
        obj->Update(deltaTime);
    }
}

void ObjectManager::RemoveObject(Object* objPtr)
{
    objects.erase(std::remove_if(objects.begin(), objects.end(),
        [&](const std::shared_ptr<Object>& o) { return o.get() == objPtr; }),
        objects.end());
}
