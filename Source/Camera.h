#ifndef _H_CAMERA
#define _H_CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

/* TODO
 * Camera is temporarily keyboard controlled movement
 * and mouse controlled rotation, but should be changed
 * to mouse controlled rotation-only about a 3D axis
 * 360 degrees
 * */

class Camera{
public:
    Camera() = default;
    ~Camera() = default;

    void update(float delta);

private:
    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view_m = glm::mat4(1.0f);

    float velocity = 0.0f;
};

#endif