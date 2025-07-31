#include "CollisionManager.h"

void CollisionManager::AddObject(std::shared_ptr<CollisionObject> obj)
{
	m_objects.push_back(obj);
}
void CollisionManager::AddObjects(std::vector<std::shared_ptr<CollisionObject>> objs)
{
	for (std::shared_ptr<CollisionObject> obj : objs)
	{
		m_objects.push_back(obj);
	}
}
void CollisionManager::SetObjects(std::vector<std::shared_ptr<CollisionObject>> objs)
{
	RemoveAllObjects();
	m_objects = objs;
}
void CollisionManager::RemoveAllObjects()
{
	m_objects.clear();
}
void CollisionManager::Update()
{
    const size_t count = m_objects.size();

    for (size_t i = 0; i < count; ++i) {
        auto objA = m_objects[i];
        if (objA->GetCollisionType() == NOCOLLISION) continue;

        for (size_t j = i + 1; j < count; ++j) {
            auto objB = m_objects[j];
            if (objB->GetCollisionType() == NOCOLLISION) continue;

            if (objA->CheckCollision(*objB)) {
                objA->OnCollision(*objB);
                objB->OnCollision(*objA);
            }
        }
    }
}