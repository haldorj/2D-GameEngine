#pragma once
#include "Character.h"
#include "../Animations/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"

#define JUMP_TIME 10.0f
#define JUMP_FORCE -200.0f

class Knight : public Character
{
public:
    Knight(Properties* properties);
    
    virtual void Draw();
    virtual void Update(float deltaTime);
    virtual void Clean();
private:
    bool m_IsJumping;
    bool m_IsOnGround;

    float m_JumpTime;
    float m_JumpForce;

    Collider* m_Collider;
    
    Animation* m_Animation;
    RigidBody* m_RigidBody;

    glm::vec2 m_LastSafePosition;
};
