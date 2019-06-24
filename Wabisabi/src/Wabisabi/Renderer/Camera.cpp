#include "wbpch.h"
#include "Camera.h"
namespace Wabisabi
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& front, float speed, float sensitivity, const glm::vec3& up)
		:m_Position(position),m_Front(front),m_Speed(speed),m_Sensitivity(sensitivity),m_Up(up),m_LookAt(glm::mat4(1.f)),m_Yaw(-90.f),m_Pitch(0.f)
	{
		Update();
	}

	void Camera::Update()
	{
		m_LookAt = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::ProcessMovement(CameraMove move)
	{
		switch (move)
		{
		case CameraMove::Forward:
			m_Position += m_Speed * m_Front;
			break;
		case CameraMove::Backward:
			m_Position -= m_Speed * m_Front;
			break;
		case CameraMove::Left:
			m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed;
			break;
		case CameraMove::Right:
			m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed;
			break;
		default:
			break;
		}
	}

	void Camera::ProcessRotation(float offsetX, float offsetY)
	{
		offsetX *= m_Sensitivity;
		offsetY *= m_Sensitivity;

		m_Yaw += offsetX;
		m_Pitch += offsetY;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 tempfront;
		tempfront.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
		tempfront.y = sin(glm::radians(m_Pitch));
		tempfront.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
		m_Front = glm::normalize(tempfront);
	}

}
