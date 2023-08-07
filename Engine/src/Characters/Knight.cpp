#include "Knight.h"
#include "../Graphics/TextureManager.h"

Knight::Knight(Properties* properties) : Character(properties)
{
    m_Animation = new Animation();
    m_Animation->SetProperties(m_TextureID, 0, 4, 120);
}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Knight::Update(float deltaTime)
{
    m_Animation->Update();
}

void Knight::Clean()
{
    TextureManager::GetInstance()->Clean();
}
