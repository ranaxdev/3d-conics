#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Harness.h"

conics::Harness::Harness(const conics::Window &w) : w(w){
}


void conics::Harness::run(conics::Harness* h) {
    // GLFW init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window
    GLFWwindow* window = glfwCreateWindow(w.width, w.height, w.title, nullptr, nullptr);
    if(window == nullptr){
        // TODO
        // Log error msg here
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Load GLAD
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        // TODO
        // Log error msg here
        glfwTerminate();
    }

    startup();

    render((float) glfwGetTime());
}

void conics::Harness::startup() {}

void conics::Harness::render(float currentTime) {}






