#ifndef CAMERA_H
#define CAMERA_H

#include "../glm/mat4x4.hpp"

class Camera {
public:
    glm::mat4 getViewMatrix() const { return viewMatrix; };

    Camera();

    void moveLeft(const float value);

private:
    glm::mat4 viewMatrix;
    glm::vec3 position;
};


#endif //CAMERA_H
