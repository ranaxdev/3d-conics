#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Harness.h"

class Test : public conics::App{
public:

};

int main(){
    Test t;
    t.startup();
    return 0;
}

/*
const float one = 1.0f;
const GLfloat color[] = {1.0f, 1.0f, 0.0f, 1.0f};

int main() {
    // GLFW init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window
    GLFWwindow* window = glfwCreateWindow(640, 480, "3D Conics", nullptr, nullptr);
    if(window == nullptr){
        std::cout << "[ERROR] Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load glad
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "[ERROR] Failed to load GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    while(!glfwWindowShouldClose(window)){
        glClearBufferfv(GL_COLOR, 0, color);
        glClearBufferfv(GL_DEPTH, 0, &one);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
*/