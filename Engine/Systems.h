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
            MovementComponent* velocity = entity.GetComponent<MovementComponent>();

            if (transform && velocity)
            {
                // Update entity's position based on velocity.
            }
        }
    }
};

class CollisionSystem {
public:
    void Update(SDL_Renderer* renderer, std::vector<Entity>& entities)
    {
        // Iterate through each entity
        for (Entity& entity : entities)
        {
            // Get the collision and transform components of the current entity
            TransformComponent* transform = entity.GetComponent<TransformComponent>();
            CollisionComponent* collision = entity.GetComponent<CollisionComponent>();

            if (collision && transform)
            {
                // Collision boxes
                // DrawCollisionBox(renderer, transform->Position, collision->BoxCollider);
                //
                // Check collisions with other entities
                for (Entity& otherEntity : entities)
                {
                    if (&entity == &otherEntity)
                        continue; // Skip self

                    // Get the collision and transform components of the other entity
                    CollisionComponent* otherCollision = otherEntity.GetComponent<CollisionComponent>();
                    TransformComponent* otherTransform = otherEntity.GetComponent<TransformComponent>();

                    if (otherCollision && otherTransform)
                    {
                        // Check for collision between the two entities' colliders
                        if (CheckCollision(transform->Position, collision->BoxCollider,
                            otherTransform->Position, otherCollision->BoxCollider))
                        {
                            // Handle collision based on tags (if needed)
                            if (collision->Tag == "Player" && otherCollision->Tag == "Coin")
                            {
                                CollectCoin(entity, otherEntity);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    bool CheckCollision(const glm::vec2& posA, const glm::vec2& colliderA,
        const glm::vec2& posB, const glm::vec2& colliderB)
    {
        // Calculate the bounding boxes of the two colliders
        glm::vec2 minA = posA - colliderA * 0.5f;
        glm::vec2 maxA = posA + colliderA * 0.5f;
        glm::vec2 minB = posB - colliderB * 0.5f;
        glm::vec2 maxB = posB + colliderB * 0.5f;

        // Check for overlap in the x-axis
        if (maxA.x >= minB.x && minA.x <= maxB.x)
        {
            // Check for overlap in the y-axis
            if (maxA.y >= minB.y && minA.y <= maxB.y)
            {
                // Collision detected
                return true;
            }
        }
        // No collision
        return false;
    }

    void CollectCoin(Entity& playerEntity, Entity& coinEntity)
    {
        coinEntity.MarkForDeletion();
    }

    void DrawCollisionBox(SDL_Renderer* renderer, const glm::vec2& position, const glm::vec2& collider)
    {
        // Scale factor to make the collision box more visible
        const float scaleFactor = 1.0f;

        // Calculate the width and height of the rectangle
        int width = static_cast<int>(collider.x * scaleFactor);
        int height = static_cast<int>(collider.y * scaleFactor);

        SDL_Rect rect = { position.x, position.y, width, height };

        // Set the draw color for the renderer
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color (R, G, B, A)
        SDL_RenderFillRect(renderer, &rect);
        
        //SDL_RenderDrawRect(renderer, &rect);
    }
};

