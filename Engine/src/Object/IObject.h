#pragma once

class IObject
{
public:
    virtual ~IObject() = default;
    virtual void Draw() {}
    virtual void Update(float deltaTime) {}
    virtual void Clean() {}
};