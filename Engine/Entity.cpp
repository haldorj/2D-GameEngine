#include "Entity.h"

int Entity::m_NextId = 0;

Entity::Entity() : m_Id(m_NextId++) {}

void Entity::AddComponent(Component* component)
{
    m_Components.push_back(component);
}

void Entity::MarkForDeletion()
{
    m_IsMarkedForDeletion = true;
}

bool Entity::IsMarkedForDeletion()
{
    return m_IsMarkedForDeletion;
}
