#pragma once
#include <glm/glm.hpp>
#include <SDL.h>

#include "../Core/Engine.h"

class Camera
{
public:
    static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

    void Update(float deltaTime);
    SDL_Rect GetCameraView() { return m_CameraView; }
    glm::vec2 GetPosition() { return m_Position; }
    void SetTarget(glm::vec2 target) { m_Target = target; }
private:
    Camera() { m_CameraView = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }

    SDL_Rect m_CameraView;
    glm::vec2 m_Target;
    glm::vec2 m_Position;
    
    static Camera* s_Instance;
};
