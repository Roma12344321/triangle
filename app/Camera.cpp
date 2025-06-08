#include "Camera.h"

#include "../glm/gtc/matrix_transform.hpp"

Camera::Camera() {
    viewMatrix = glm::mat4(1.f);
    position = glm::vec3(0, 0, 0.f);
    viewMatrix = glm::translate(viewMatrix, position);
}

void Camera::moveLeft(const float value) {
    viewMatrix = glm::mat4(1.f);
    position = glm::vec3(position.x + value, position.y, 0.f);
    viewMatrix = glm::translate(viewMatrix, position);
}
