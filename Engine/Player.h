#pragma once

#include <iostream>
#include "Entity.h"

class Player : public Entity
{
public:
    Player(SDL_Renderer* renderer);
    void HandleInput(const Uint8* keystates, float deltaTime);
    void Update(float deltaTime);

private:
    float m_JumpTimer = 0.5f;
    float m_Speed = 0.4;
    float m_Gravity = 0.002f;
    float m_JumpForce = 1.f;

    bool IsJumping;
    bool IsFalling;
    bool IsOnGround;

    SDL_Renderer* m_Renderer;

    glm::vec2 m_MovementState;

    SpriteComponent* m_Sprite;
    TransformComponent* m_Transform;
    MovementComponent* m_Movement;
    CollisionComponent* m_Collision;
    KeyInputComponent* m_KeyInput;
};