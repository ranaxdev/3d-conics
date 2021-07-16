#include "Camera.h"
#include <iostream>

void Camera::update(float delta) {
    Camera::velocity = 8.0f * delta;
}

glm::mat4 &Camera::calc_VP(float delta) {
    Camera::velocity = 8.0f * delta;

    Camera::view_m = glm::lookAt(cam_pos, cam_pos+cam_front, cam_up);
    Camera::vp_m = Camera::proj_m * Camera::view_m;
    return Camera::vp_m;
}

const int &Camera::pressed(const int& keycode) {

    if(keycode == FWD)
        cam_pos += velocity * cam_front;
    if(keycode == BCK)
        cam_pos -= velocity * cam_front;
    if(keycode == LFT)
        cam_pos -= glm::normalize(glm::cross(cam_front, cam_up))*velocity;
    if(keycode == RGT)
        cam_pos += glm::normalize(glm::cross(cam_front, cam_up))*velocity;

    return KeyListener::pressed(keycode);
}
