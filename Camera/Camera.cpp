#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {

	Position = position;
	WordUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WordUp));
	Up = glm::normalize(glm::cross(Forward, Right));
	
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	Position = position;
	WordUp = worldup;
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
	Right = glm::normalize(glm::cross(Forward, WordUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

glm::mat4 Camera::GetViewMatrix() {

	return glm::lookAt(Position, Position + Forward, WordUp);
}

void Camera::SetCameraPosition(glm::vec3 position) {
	Position = position;
}


Camera::~Camera() {


}