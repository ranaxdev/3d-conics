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
    Mesh* mesh;
    std::shared_ptr<Spawner> spawner;

    void startup() override {

        spawner = std::make_shared<Spawner>();
        mesh = new Mesh(surface::DOUBLE_CONE, 2.0f, 2.0f, 1.0f, 20);
    };


    void render(float delta) override {
        VP = camera->calc_VP(delta);

        // Mesh Generation
        if(spawner->mesh_generated){
            delete mesh->menu;
            delete mesh;
            mesh = new Mesh(spawner->current_surface, spawner->alpha, spawner->beta, 1.0f, spawner->lod);
        }
        // GUI
        R->renderGUI(*spawner);

        // MESH
        R->renderMesh(*mesh);

    }
};


#define DEBUG 0
#if !DEBUG
int main(){
    conics::Window window = conics::Window(1920, 1080, "conics", 0.1f, 0.12f, 0.15f);
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