#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMove
{
	Forward,Backward,Left,Right,
};
namespace Wabisabi
{
	class Camera
	{
	public:
	public:
		Camera(const glm::vec3& position, const glm::vec3& front,float speed,float sensitivity, const glm::vec3& up = {0.f,1.f,0.f});
		void Update();
		void ProcessMovement(CameraMove move);
		void ProcessRotation(float offsetX,float offsetY);
		inline const glm::mat4& GetView() const { return m_LookAt; };
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::mat4 m_LookAt;
		float m_Speed;
		float m_Sensitivity;
		float m_Yaw;
		float m_Pitch;
	};
}