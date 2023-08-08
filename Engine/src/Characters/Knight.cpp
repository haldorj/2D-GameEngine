#include "Knight.h"
#include "../Graphics/TextureManager.h"
#include "../Inputs/Input.h"

Knight::Knight(Properties* properties) : Character(properties)
{
    m_Animation = new Animation();
    
    m_RigidBody = new RigidBody();
}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Knight::Update(float deltaTime)
{
    m_RigidBody->StopForce();
    m_Animation->SetProperties(m_TextureID, 1, 5, 100);
    // Running
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody->ApplyForceX(20 * FORWARD);
        m_Animation->SetProperties(m_TextureID, 3, 7, 100);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody->ApplyForceX(20 * BACKWARD);
        m_Animation->SetProperties(m_TextureID, 3, 7, 100, SDL_FLIP_HORIZONTAL);
    }
    
    m_RigidBody->Update(deltaTime);
    m_Transform->TranslateX(m_RigidBody->GetPosition().x);
    //m_Transform->TranslateY(m_RigidBody->GetPosition().y);

    m_Origin.x = m_Transform->X + m_Width/2;
    m_Origin.y = m_Transform->Y + m_Height/2;
    
    m_Animation->Update();
}

void Knight::Clean()
{
    TextureManager::GetInstance()->Clean();
}
