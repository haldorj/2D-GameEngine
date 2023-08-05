#pragma once

#include "Components.h"
#include "Entity.h"

#include <vector>

class RenderSystem {
public:
    void Update(std::vector<Entity>& entities) 
    {
        for (Entity& entity : entities) 
        {
            TransformComponent* transform = entity.GetComponent<TransformComponent>();
            SpriteComponent* sprite = entity.GetComponent<SpriteComponent>();

            if (transform && sprite) 
            {
                sprite->Sprite->Render(transform->Position);
            }
        }
    }
};

class NPCMovementSystem {
public:
    void Update(std::vector<Entity>& entities)
    {
        for (Entity& entity : entities)
        {
            TransformComponent* transform = entity.GetComponent<TransformComponent>();
            VelocityComponent* velocity = entity.GetComponent<VelocityComponent>();

            if (transform && velocity)
            {
                // Update entity's position based on velocity.
            }
        }
    }
};