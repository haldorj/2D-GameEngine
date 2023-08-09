#include "Knight.h"
#include "../Graphics/TextureManager.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionHandler.h"

Knight::Knight(Properties* properties) : Character(properties)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(50.0f);
    
    m_Animation = new Animation();
}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    // Draw collision debug box
    m_Collider->DrawDebugRect();
}

void Knight::Update(float deltaTime)
{
    m_RigidBody->StopForce();
    m_Animation->SetProperties(m_TextureID, 1, 5, 100);
    // Running
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody->ApplyForceX(20);
        m_Animation->SetProperties(m_TextureID, 3, 7, 100);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody->ApplyForceX(-20);
        m_Animation->SetProperties(m_TextureID, 3, 7, 100, SDL_FLIP_HORIZONTAL);
    }

    // Jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsOnGround)
    {
        std::cout << "jump \n";
        m_IsJumping = true;
        m_IsOnGround = false;
        m_RigidBody->ApplyForceY(m_JumpForce);
    }

    if (m_IsJumping && !m_IsOnGround && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_JumpTime > 0)
    {
        std::cout << "continue jump \n";
        m_JumpTime -= deltaTime;
        m_RigidBody->ApplyForceY(m_JumpForce);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // Move on X axis
    m_RigidBody->Update(deltaTime);
    m_LastSafePosition.x = m_Transform->X;
    m_Transform->TranslateX(m_RigidBody->GetPosition().x);
    m_Collider->SetCollider(m_Transform->X, m_Transform->Y, 96, 96);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetCollider()))
        m_Transform->X = m_LastSafePosition.x;

    // Move on Y axis
    m_RigidBody->Update(deltaTime);
    m_LastSafePosition.y = m_Transform->Y;
    m_Transform->TranslateY(m_RigidBody->GetPosition().y);
    m_Collider->SetCollider(m_Transform->X, m_Transform->Y, 96, 96);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetCollider()))
    {
        m_IsOnGround = true;
        m_Transform->Y = m_LastSafePosition.y;
    }
    else
    {
        m_IsOnGround = false;
    }
    
    m_Origin.x = m_Transform->X + m_Width/2;
    m_Origin.y = m_Transform->Y + m_Height/2;

    if (m_IsJumping || !m_IsOnGround)
        m_Animation->SetProperties(m_TextureID, 4, 8, 100);
    
    m_Animation->Update();
}

void Knight::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
