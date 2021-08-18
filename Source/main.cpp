#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    std::shared_ptr<Spawner> spawner;

    void startup() override {
        R->default_mesh = new Mesh(surface::DOUBLE_CONE, 2.0f, 2.0f, 1.0f, 20);

        spawner = std::make_shared<Spawner>();

    };


    void render(float delta) override {
        VP = camera->calc_VP(delta);

        // GUI
        R->renderGUI(*spawner);

        // MESH (use default or create your own initial one)
        R->renderMesh(*R->default_mesh);

    }
};


#if !DEBUG
int main(){
    conics::Window window = conics::Window(1920, 1080, "conics", 0.03f, 0.04f, 0.07f);
    App* a = new App;
    a->setWindow(window);
    a->run(a);

    delete a;
    
    return 0;
}


#else


#include <sqlite3.h>
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    std::cout << argc << std::endl;
    for(i = 0; i<argc; i++) {
        printf("%i, %s = %s\n", i, azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(){

    sqlite3* db;
    char* err = nullptr;
    int rc;
    std::cout << (SRC+"surfaceDB.sqlite").c_str() << std::endl;
    rc = sqlite3_open((SRC+"surfaceDB.sqlite").c_str(), &db);

    if(rc){
        std::cout << "Not opened" << std::endl;
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    else{
        std::cout << "opened" << std::endl;
    }
    const char* sql = "SELECT * FROM surface WHERE surface_ID=2;";
    rc = sqlite3_exec(db, sql, callback, nullptr, &err);
    if (rc != SQLITE_OK){
        std::cout << "Failed" << std::endl;
        sqlite3_free(err);
    }
    else{
        std::cout << "OK" << std::endl;
    }
    sqlite3_close(db);
    return 0;
}

#endif