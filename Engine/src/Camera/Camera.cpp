#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float deltaTime)
{
    m_CameraView.x = m_Target.x - SCREEN_WIDTH / 2;
    m_CameraView.y = m_Target.y - SCREEN_HEIGHT / 2;

    if (m_CameraView.x < 0)
        m_CameraView.x = 0;

    if (m_CameraView.y < 0)
        m_CameraView.y = 0;

    if (m_CameraView.x > (2*SCREEN_WIDTH - m_CameraView.w))
        m_CameraView.x = (2*SCREEN_WIDTH - m_CameraView.w);

    if (m_CameraView.y > (SCREEN_HEIGHT - m_CameraView.h))
        m_CameraView.y = (SCREEN_HEIGHT - m_CameraView.h);

    m_Position = glm::vec2(m_CameraView.x, m_CameraView.y);
}
