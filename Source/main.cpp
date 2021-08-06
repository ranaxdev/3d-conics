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

    void startup() override {

        renderer->shader_axis.bind();
        renderer->enableAxis();


        shader2 = new Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");
        shader2->bind();
        std::vector<GLfloat> data2 = {
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.23f, 0.0f,
                0.23f, 0.75f, 0.0f,
                -1.0f, -0.75f, 0.0f,
                0.73f, -0.40f, 0.0f,
                0.69f, 0.69f, 0.0f,
                1.0f, -0.88f, 0.0f
        };
        auto i = renderer->prepBuf(data2);
        renderer->formatBuf(i, 3, {3}, *shader2);
    };

    float delta = 0.0f;
    float last = 0.0f;

    void render(float currentTime) override {
        delta = currentTime - last;

        glPointSize(20.0f);
        glLineWidth(1.0f);

        shader2->bind();
        shader2->setMat4(20, camera->calc_VP(delta));
        shader2->setVec4(30, cyan);
        glDrawArrays(GL_POINTS, 0, 7);


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
    conics::Window window = conics::Window(1280, 960, "conics");
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

    std::unordered_set<int, const char*> set;

    return 0;
}

#endif