#pragma once

#include <SDL.h>

#include <glm/glm.hpp>
#include "Texture.h"

// Parent struct
struct Component
{
    virtual void Update() {};
};

struct SpriteComponent : public Component
{
    Texture* Sprite = nullptr;
};

struct TransformComponent : public Component
{
    glm::vec2 Position = glm::vec2(0.0f, 0.0f);
};

struct MovementComponent : public Component
{
    glm::vec2 Velocity = glm::vec2(0.0f, 0.0f);
    float Acceleration = 0.0f;
    float Deceleration = 0.0f;
};

struct CollisionComponent : public Component
{
    std::string Tag = "";
    glm::vec2 BoxCollider = glm::vec2(0.0f, 0.0f);
};

struct KeyInputComponent : public Component
{
};