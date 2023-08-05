#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
    // Create components and assign them to member variables
    m_Sprite = new SpriteComponent();
    m_Sprite->Sprite = new Texture(renderer, "../Textures/player.png");

    m_Transform = new TransformComponent();
    m_Transform->Position.x = 100.0f;
    m_Transform->Position.y = 400.0f;

    m_Movement = new MovementComponent();
    m_Movement->Velocity.x = 0.0;
    m_Movement->Velocity.y = 0.0;
    m_Movement->Acceleration = 0.0010;
    m_Movement->Deceleration = 0.0010;

    m_KeyInput = new KeyInputComponent();

    // Add the components to the entity
    AddComponent(m_Sprite);
    AddComponent(m_Transform);
    AddComponent(m_Movement);
    AddComponent(m_KeyInput);
}

void Player::HandleInput(const Uint8* keystates, float deltaTime)
{
    // Update the player's velocity based on keys

    if (keystates[SDL_SCANCODE_A]) {
        m_Movement->Velocity.x = std::max(m_Movement->Velocity.x - m_Movement->Acceleration * deltaTime, -m_Speed);
    }
    else if (keystates[SDL_SCANCODE_D]) {
        m_Movement->Velocity.x = std::min(m_Movement->Velocity.x + m_Movement->Acceleration * deltaTime, m_Speed);
    }
    else {
        // Apply deceleration when no movement keys are pressed
        if (m_Movement->Velocity.x > 0) {
            m_Movement->Velocity.x -= m_Movement->Deceleration * deltaTime;
            if (m_Movement->Velocity.x < 0) {
                m_Movement->Velocity.x = 0;
            }
        }
        else if (m_Movement->Velocity.x < 0) {
            m_Movement->Velocity.x += m_Movement->Deceleration * deltaTime;
            if (m_Movement->Velocity.x > 0) {
                m_Movement->Velocity.x = 0;
            }
        }
    }

    if (keystates[SDL_SCANCODE_SPACE] && IsOnGround)
    {
        m_Movement->Velocity.y = -m_JumpForce;
        IsJumping = true;
        IsOnGround = false;
    }
}

void Player::Update(float deltaTime)
{
    // Apply gravity for falling if not jumping and not on ground
    if (!IsOnGround && !IsJumping)
    {
        m_Movement->Velocity.y += m_Gravity * deltaTime; // Adjust the fall gravity value
        IsFalling = true;
    }

    // Update player's position based on velocity and delta time
    m_Transform->Position.x += m_Movement->Velocity.x * deltaTime;
    m_Transform->Position.y += m_Movement->Velocity.y * deltaTime;

    // Boundaries check
    if (m_Transform->Position.x <= 0)
    {
        m_Transform->Position.x = 0;
    }
    if (m_Transform->Position.x >= 740)
    {
        m_Transform->Position.x = 740;
    }
    if (m_Transform->Position.y <= 0)
    {
        m_Transform->Position.y = 0;
    }

    // Ground check
    if (m_Transform->Position.y >= 500)
    {
        m_Transform->Position.y = 500;
        m_Movement->Velocity.y = 0;
        IsJumping = false;
        IsFalling = false;
        IsOnGround = true;
    }

    // Handle jumping logic
    if (IsJumping)
    {
        IsJumping = false;
    }
}