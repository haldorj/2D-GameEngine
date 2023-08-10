#pragma once
#include "Character.h"
#include "../Animations/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"

#define LEFT (-1.0f)
#define RIGHT 1.0f
#define UP 1.0f
#define DOWN (-1.0f)

#define JUMP_TIME 1.0f
#define ATTACK_TIME 0.12f

#define RUN_FORCE 1200.f
#define JUMP_FORCE (-8000.f)
#define GRAVITY 1500.f

class Knight : public Character
{
public:
    Knight(Properties* properties);
    
    void Draw() override;
    void Update(float deltaTime) override;
    void Clean() override;
private:
    void AnimationState();
    
    bool m_IsRunning ;
    bool m_IsJumping;
    bool m_IsFalling;
    bool m_IsOnGround;
    bool m_IsCrouching;
    bool m_IsAttacking;
    
    float m_JumpTime;
    float m_JumpForce;
    float m_AttackTime;

    Collider* m_Collider;
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    glm::vec2 m_LastSafePosition;
};
