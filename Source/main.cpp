#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

#include "Math.h"
#include "Logger.h"
#include "Globals.h"


using namespace conics;


class App : public conics::Harness{
public:

    std::shared_ptr<Camera> camera;
    Mesh* m;

    void startup() override {

        R->enableAxis();
        m = new Mesh(surface::DISC, 5.0f, 5.0f, 1.0f, 20);
    };


    void render(float delta) override {
        VP = camera->calc_VP(delta);

        // MESH
        R->renderMesh(*m);

        // AXES
        R->renderAxis();

    }
};


#define DEBUG 0
#if !DEBUG
int main(){
    conics::Window window = conics::Window(1920, 1080, "conics", 0.0f, 0.0f, 0.0f);
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