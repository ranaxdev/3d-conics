#ifndef _H_CAMERA
#define _H_CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils/KeyListener.h"

// Direction constants - may change depending on util lib
#define FWD GLFW_KEY_W
#define BCK GLFW_KEY_S
#define LFT GLFW_KEY_A
#define RGT GLFW_KEY_D


/* TODO
 * Camera is temporarily keyboard controlled movement
 * and mouse controlled rotation, but should be changed
 * to mouse controlled rotation-only about a 3D axis
 * 360 degrees
 * */

class Camera : public KeyListener{
public:
    Camera() = default; // temp
    ~Camera() = default;

    glm::mat4& calc_VP(float delta);

    // Getters
    const glm::vec3& getCamPos() const;

private:
    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view_m = glm::mat4(1.0f);
    glm::mat4 proj_m = glm::perspective(glm::radians(55.0f), 4.0f/3.0f, 0.1f, 100.0f);
    glm::mat4 vp_m = glm::mat4(1.0f);

    const float sens = 0.1f;
    float velocity = 0.0f;
    double xoff = 0.0, yoff = 0.0;
    double lastX = xoff, lastY = yoff;
    double yaw = -90.0, pitch = 0.0;
};

#endif