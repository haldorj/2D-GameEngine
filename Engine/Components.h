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
    Texture* Sprite;
};

struct TransformComponent : public Component
{
    glm::vec2 Position;
};

struct VelocityComponent : public Component
{
    glm::vec2 Velocity;
};

struct KeyInputComponent : public Component
{
    bool upKey = false;
    bool downKey = false;
    bool leftKey = false;
    bool rightKey = false;
};