#include "YObjectManager.h"



YObjectManager& YObjectManager::GetInstance()
{
    static YObjectManager instance;
    return instance;
}

void YObjectManager::AddObject(std::shared_ptr<YObject> obj)
{
    objects.push_back(obj);
}

void YObjectManager::UpdateAll(float deltaTime)
{
    for (auto& obj : objects) {
        obj->Update(deltaTime);
    }
}

void YObjectManager::RemoveObject(YObject* objPtr)
{
    objects.erase(std::remove_if(objects.begin(), objects.end(),
        [&](const std::shared_ptr<YObject>& o) { return o.get() == objPtr; }),
        objects.end());
}
