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
    // Window settings
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, (void*)(this)); // Pointer to app window that implements this harness

    // Callbacks
    glfwSetKeyCallback(window, conics::key_callback);

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
            if(currentAction == GLFW_PRESS)
                o->pressed(currentKey);
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

void conics::Harness::addKeyListener(KeyListener* k) {
    Harness::keylisteners.push_back(k);
}

void conics::Harness::setKA(const int &key, const int &action) {
    Harness::currentKey = key;
    Harness:currentAction = action;
}

void conics::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Retrieve harness of current window
    Harness* instance = (Harness*)glfwGetWindowUserPointer(window);

    // Send key info to application that implements the harness
    if(instance){
        instance->setKA(key, action);
    }
}
