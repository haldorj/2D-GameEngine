#pragma once

#include "glm/glm.hpp"

#define UNIT_MASS 1.0f
#define GRAVITY 9.81f;

class RigidBody
{
public:
    RigidBody(): m_Force(), m_Friction(), m_Position(), m_Velocity(), m_Acceleration()
    {
        m_Mass = UNIT_MASS;
        m_Gravity = GRAVITY;
    }

    void SetMass(float mass) { m_Mass = mass; }
    void SetGravity(float gravity) { m_Gravity = gravity; }

    void ApplyForce(glm::vec2 force) { m_Force = force; }
    void ApplyForceX(float force) { m_Force.x = force; }
    void ApplyForceY(float force) { m_Force.y = force; }
    void StopForce() { m_Force = glm::vec2(0.0f,0.0f); }

    void ApplyFriction(glm::vec2 friction) { m_Friction = friction; }
    void StopFriction() { m_Friction = glm::vec2(0.0f,0.0f); }

    float GetMass() { return m_Mass; }
    glm::vec2 GetPosition() { return m_Position; }
    glm::vec2 GetVelocity() { return m_Velocity; }
    glm::vec2 GetAcceleration() { return m_Acceleration; }

    void Update(float deltaTime)
    {
        m_Acceleration.x = (m_Force.x + m_Friction.x)/m_Mass;
        m_Acceleration.y = m_Gravity + (m_Force.y/m_Mass);
        m_Velocity = m_Acceleration * deltaTime;
        m_Position = m_Velocity * deltaTime;
    }
    
private:
    float m_Mass;
    float m_Gravity;

    glm::vec2 m_Force;
    glm::vec2 m_Friction;

    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    glm::vec2 m_Acceleration;
};