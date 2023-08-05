#pragma once

#include <iostream>

#include "Entity.h"

class Player : public Entity
{
public:
    Player(SDL_Renderer* renderer);
    void HandleInput(const Uint8* keystates);
    void Update(float deltaTime);

private:
    float Speed = 0.4;
    float JumpForce = 1.6f;
    float Gravity = 0.004f;

    bool IsJumping;
    bool IsFalling;
    bool IsOnGround;

    SDL_Renderer* renderer;

    glm::vec2 m_MovementState;
    SpriteComponent* m_Sprite;
    TransformComponent* m_Transform;
    MovementComponent* m_Movement;
    KeyInputComponent* m_KeyInput;
};