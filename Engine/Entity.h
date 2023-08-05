#pragma once

#include "Components.h"
#include <vector>

class Entity
{
public:
    Entity();

    void AddComponent(Component* component);

    template <typename T>
    T* GetComponent()
    {
        for (Component* component : m_Components)
        {
            T* castComponent = dynamic_cast<T*>(component);
            if (castComponent)
                return castComponent;
        }
        return nullptr;
    }

    void MarkForDeletion();
    bool IsMarkedForDeletion();

private:
    int m_Id;
    std::vector<Component*> m_Components;
    static int m_NextId;

    bool m_IsMarkedForDeletion = false;
};