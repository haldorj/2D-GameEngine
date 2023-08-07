#pragma once
#include "Character.h"
#include "../Animations/Animation.h"
#include "../Physics/RigidBody.h"

class Knight : public Character
{
public:
    Knight(Properties* properties);
    
    virtual void Draw();
    virtual void Update(float deltaTime);
    virtual void Clean();
private:
    Animation* m_Animation;
    RigidBody* m_RigidBody;
};
