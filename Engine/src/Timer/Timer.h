#pragma once

const float TARGET_FPS = 60.0f;
const float TARGET_DELTATIME = 0.1f;

class Timer
{
public:
    static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

    void Tick();
    float GetDeltaTime() const { return m_DeltaTime; }
    
private:
    Timer(){}
    static Timer* s_Instance;
    float m_DeltaTime = 0;
    float m_LastTime = 0;
    
};
