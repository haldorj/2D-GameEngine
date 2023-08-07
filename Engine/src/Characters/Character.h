#pragma once

#include "../Object/GameObject.h"
#include <string>

class Character : public GameObject
{
public:
    Character(Properties* properties) : GameObject(properties) {}
    
    virtual void Draw() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Clean() = 0;
    
protected:
    std::string m_Name;
};