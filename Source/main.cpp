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


    // Indexed drawing stuff
    int size =0;
    int detail = 50;
    float range = (float)detail/2;
    std::vector<GLfloat> points;

    void startup() override {
        shader2 = new Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");


        R->enableAxis();

        R->setupParaboloid(1.0f, 1.0f, detail);

    };

    float delta = 0.0f;
    float last = 0.0f;

    void render(float currentTime) override {
        delta = currentTime - last;
        VP = camera->calc_VP(delta);

        R->renderParaboloid(R->shader_gen);


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