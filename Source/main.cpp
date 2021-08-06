#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>


#include "Harness.h"
#include "Shader.h"
#include "Camera.h"
#include "Renderer.h"

#include "Utils/Math.h"
#include "Utils/Logger.h"
#include "Utils/Globals.h"


using namespace conics;
class App : public conics::Harness{
public:

    std::shared_ptr<Camera> camera;
    Shader* shader;
    Shader* shader2;

    // Colors
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

    // Indexed drawing stuff
    int size =0;
    std::vector<GLfloat> points;

    void startup() override {

        renderer->shader_axis.bind();
        renderer->enableAxis();

    };

    float delta = 0.0f;
    float last = 0.0f;

    void render(float currentTime) override {
        delta = currentTime - last;

        glPointSize(20.0f);
        glLineWidth(10.0f);

        shader2->bind();
        shader2->setMat4(20, camera->calc_VP(delta));
        shader2->setVec4(30, cyan);

        // AXES
        glLineWidth(20.0f);
        renderer->shader_axis.bind();
        renderer->shader_axis.setMat4(20, camera->calc_VP(delta));
        glDrawArrays(GL_LINES , 0, 8);

        last = currentTime;
    }
};


#define DEBUG 0
#if !DEBUG
int main(){
    conics::Window window = conics::Window(1280, 960, "conics", 0.0f, 0.0f, 0.0f);
    std::shared_ptr<Camera> camera(new Camera);
    App* a = new App;
    a->setWindow(window);
    a->addKeyListener(camera);
    a->camera = camera;

    a->run(a);
    delete a;
    
    return 0;
}


#else



int main(){
    
    return 0;
}

#endif