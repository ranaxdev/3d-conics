#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Harness.h"
#include <vector>


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

    // Application Rendering
    const GLfloat screen_color[4] = {w.color[0], w.color[1], w.color[2], w.color[3]};
    while(!glfwWindowShouldClose(window)){
        glClearBufferfv(GL_COLOR, 0, screen_color);

        // Update observers
        for(auto& o : conics::Harness::keylisteners){
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                o->pressed(GLFW_KEY_W);
            }
        }

        // Render
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

void conics::Harness::addKeyListener(const KeyListener* k) {
    Harness::keylisteners.push_back(k);
}

