#include "Camera.h"
#include <iostream>

void Camera::update(float delta) {
    Camera::velocity = 8.0f * delta;
}

const int &Camera::pressed(const int &keycode) const {
    std::cout << keycode << std::endl;
    return KeyListener::pressed(keycode);
}
