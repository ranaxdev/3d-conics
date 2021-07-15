#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Harness.h"



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

    // Application Initialization
    startup();

    // Application Render
    while(!glfwWindowShouldClose(window)){
        render((float) glfwGetTime());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void conics::Harness::startup() {}

void conics::Harness::render(float currentTime) {}

void conics::Harness::setWindow(const conics::Window &window) {
    conics::Harness::w = window;
}

const conics::Window& conics::Harness::getWindow() const {
    return Harness::w;
}

