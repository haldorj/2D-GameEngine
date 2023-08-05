#pragma once

#include <iostream>

#include "Entity.h"

class Player : public Entity
{
public:
    Player(SDL_Renderer* renderer);
    void HandleInput(const Uint8* keystates);
    void Update(float deltaTime);

    glm::vec2 m_MovementState;
    SpriteComponent* m_Sprite;
    TransformComponent* m_Transform;
    VelocityComponent* m_Velocity;
    KeyInputComponent* m_KeyInput;
private:

    SDL_Renderer* renderer;

};