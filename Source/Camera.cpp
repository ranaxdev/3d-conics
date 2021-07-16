#include "Camera.h"
#include <iostream>


glm::mat4 &Camera::calc_VP(float delta) {
    Camera::velocity = 8.0f * delta;

    std::cout << keys[FWD] << " " << keys[BCK] << " " << keys[LFT] << " " << keys[RGT] << std::endl;
    // Update Movement
    if(keys[FWD])
        cam_pos += velocity * cam_front;
    if(keys[BCK])
        cam_pos -= velocity * cam_front;
    if(keys[LFT])
        cam_pos -= glm::normalize(glm::cross(cam_front, cam_up))*velocity;
    if(keys[RGT])
        cam_pos += glm::normalize(glm::cross(cam_front, cam_up))*velocity;


    Camera::view_m = glm::lookAt(cam_pos, cam_pos+cam_front, cam_up);
    Camera::vp_m = Camera::proj_m * Camera::view_m;
    return Camera::vp_m;
}
