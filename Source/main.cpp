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
#include "Spawner.h"
#include "Renderer.h"

#include "Math.h"
#include "Logger.h"
#include "Globals.h"


using namespace conics;
class App : public conics::Harness{
public:
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Mesh> mesh;
    Spawner* spawner;

    void startup() override {

        mesh = std::make_shared<Mesh>(surface::DISC, 2.0f, 2.0f, 1.0f, 20);
        spawner = new Spawner();
        R->enableAxis();
    };


    void render(float delta) override {
        VP = camera->calc_VP(delta);

        spawner->update();
        // MESH
        R->renderMesh(*mesh);

        // AXES
        R->renderAxis();
    }
};


#define DEBUG 0
#if !DEBUG
int main(){
    conics::Window window = conics::Window(1920, 1080, "conics", 0.0f, 0.0f, 0.0f);
    App* a = new App;
    a->setWindow(window);
    a->run(a);

    delete a;
    
    return 0;
}


#else



int main(){

    return 0;
}

#endif