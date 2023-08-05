#pragma once

#include <SDL.h>

#include <glm/glm.hpp>
#include "Texture.h"

// Parent class
class Component
{
public:
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

struct KeyInputComponent : public Component
{
};