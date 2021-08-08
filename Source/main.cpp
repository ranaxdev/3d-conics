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

    void startup() override {
//        R->setupConic(5.0f, glm::radians(360.0f), 100, 1.0f, conic::DOUBLE_CONE);


        R->enableAxis();
    };

    float delta = 0.0f;
    float last = 0.0f;

    void render(float currentTime) override {
        delta = currentTime - last;
        VP = camera->calc_VP(delta);


        R->setupSurface((float)glfwGetTime(), 1.0f, 25, 1.0f, surface::PARABOLOID);

        // SURFACES
        R->renderMesh(Renderer::surface_data);

        // AXES
        R->renderAxis();

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