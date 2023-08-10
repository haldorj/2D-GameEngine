#include "Knight.h"
#include "../Graphics/TextureManager.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionHandler.h"

Knight::Knight(Properties* properties) : Character(properties)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(GRAVITY);

    m_Animation = new Animation();
}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

    // Draw collision debug box
    //m_Collider->DrawDebugRect();
}

void Knight::Update(float deltaTime)
{
    m_IsRunning = false;
    m_IsCrouching = false;
    
    m_RigidBody->StopForce();

    // Running right
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == RIGHT && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(RUN_FORCE * RIGHT);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }
    // Running left
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == LEFT && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(RUN_FORCE * LEFT);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    // Crouching
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN))
    {
        m_RigidBody->StopForce();
        m_IsCrouching = true;
    }

    // Attacking
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_Z))
    {
        m_RigidBody->StopForce();
        m_IsAttacking = true;
    }
    
    // Jumping
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsOnGround)
    {
        m_IsJumping = true;
        m_IsOnGround = false;
        m_RigidBody->ApplyForceY(m_JumpForce);
    }
    if (m_IsJumping && !m_IsOnGround && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_JumpTime > 0)
    {
        m_JumpTime -= deltaTime;
        m_RigidBody->ApplyForceY(m_JumpForce);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    //Falling
    if (m_RigidBody->GetVelocity().y > 0 && !m_IsOnGround)
        m_IsFalling = true;
    else
        m_IsFalling = false;

    // Attack timer
    if (m_IsAttacking && m_AttackTime > 0)
    {
        m_AttackTime -= deltaTime;
    }
    else
    {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    // Collider: Move on X axis
    m_RigidBody->Update(deltaTime);
    m_LastSafePosition.x = m_Transform->X;
    m_Transform->TranslateX(m_RigidBody->GetPosition().x);
    m_Collider->SetCollider(m_Transform->X + 50, m_Transform->Y + 40, 20, 40);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetCollider()))
        m_Transform->X = m_LastSafePosition.x;

    // Collider: Move on Y axis
    m_RigidBody->Update(deltaTime);
    m_LastSafePosition.y = m_Transform->Y;
    m_Transform->TranslateY(m_RigidBody->GetPosition().y);
    m_Collider->SetCollider(m_Transform->X + 50, m_Transform->Y + 40, 20, 40);

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
    
    m_Animation->SetProperties(m_TextureID, 1, 5, 100);
    AnimationState();
    m_Animation->Update();
}

void Knight::AnimationState()
{
    m_Animation->SetProperties("knight_idle", 1, 10, 100);
    if (m_IsRunning)
        m_Animation->SetProperties("knight_run", 1, 10, 100);
    if (m_IsJumping)
        m_Animation->SetProperties("knight_jump", 1, 3, 100);
    if (m_IsFalling)
        m_Animation->SetProperties("knight_fall", 1, 3, 100);
    if (m_IsCrouching)
        m_Animation->SetProperties("knight_crouch", 1, 1, 100);
    if (m_IsAttacking)
        m_Animation->SetProperties("knight_attack", 1, 4, 100);
}

void Knight::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}