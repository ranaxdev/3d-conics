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

    std::vector<std::function<void(Shader& s)>> funcs;

    // Indexed drawing stuff
    int size =0;
    int detail = 50;
    float range = (float)detail/2;
    std::vector<GLfloat> points;

    void startup() override {
        shader2 = new Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");


        R->enableAxis();

        for(int i=0; i<detail; i++){
            for(int j=0; j<detail; j++){
                float x = 3.0f*(((float) (i-range))/range);
                float y = 3.0f*(((float) (j-range))/range);
                float z = pow(x,2) + pow(y,2);
                points.push_back(x);
                points.push_back(z);
                points.push_back(-2.5f+y);
            }
        }
        for(int i=0; i<detail; i++){
            for(int j=0; j<detail; j++){
                float x = 3.0f*(((float) (j-range))/range);
                float y = 3.0f*(((float) (i-range))/range);
                float z = pow(x,2) + pow(y,2);
                points.push_back(x);
                points.push_back(z);
                points.push_back(-2.5f+y);
            }
        }


        auto i = R->prepBuf(points);
        R->formatBuf(i, 3, {3}, *shader2);

    };

    float delta = 0.0f;
    float last = 0.0f;

    void render(float currentTime) override {
        delta = currentTime - last;
        VP = camera->calc_VP(delta);

        glPointSize(20.0f);
        glLineWidth(10.0f);

        shader2->bind();
        shader2->setMat4(20, camera->calc_VP(delta));
        shader2->setVec4(30, cyan);
        for(int i=0; i<detail; i++){
            glDrawArrays(GL_LINE_STRIP, detail*i, detail);
            glDrawArrays(GL_LINE_STRIP, points.size()/3/2+(detail*i), detail);
        }

        // AXES
        R->renderAxis(R->shader_axis);
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