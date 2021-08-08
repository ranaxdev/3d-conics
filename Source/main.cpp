#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

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
    Mesh* m;
    void startup() override {

        R->enableAxis();
        m = new Mesh(surface::DISC, 0.1f, 0.1f, 1.0f, 50);

    };

    float delta = 0.0f;
    float last = 0.0f;

    bool show_demo = true;
    void render(float currentTime) override {


        if(show_demo)
        {
            ImGui::Begin("Temp", &show_demo);
            ImGui::Text("3D Conics 3D Conics 3D Conics");
            if(ImGui::Button("Close")){
                show_demo = false;
            }
            ImGui::End();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        }

        delta = currentTime - last;
        VP = camera->calc_VP(delta);

        // MESH
        m->alpha = 0.1f*(float) glfwGetTime();
        m->beta  = 0.1f*(float) glfwGetTime();
        R->setupMesh(*m);
        R->renderMesh(Renderer::mesh_data);


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