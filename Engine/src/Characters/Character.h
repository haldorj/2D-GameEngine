#pragma once

#include "../Object/GameObject.h"
#include <string>

class Character : public GameObject
{
public:
    Character(Properties* properties) : GameObject(properties) {}

    void Draw() override {}
    void Update(float deltaTime) override {}
    void Clean() override {}

protected:
    std::string m_Name;
};