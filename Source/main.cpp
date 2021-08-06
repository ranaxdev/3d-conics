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

float func(float x, float y, float t){
    auto z = (float) (pow(x,2) + pow(y,2));
    return z;
}

struct point{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

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

        shader2 = new Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");
        shader2->bind();

        point v[101][101];
        for(int i=0; i<101; i++){
            for(int j=0; j<101; j++){
                v[i][j].x = (j-50)/50.0;
                v[i][j].z = (i-50)/50.0;
                v[i][j].y = 0;
            }
        }
        GLushort indices[2*100*101*2];
        int i=0;
        // Horizontal
        for(int y=0; y<101; y++){
            for(int x =0; x<100; x++){
                indices[i++] = y * 101 + x;
                indices[i++] = y * 101 + x + 1;
            }
        }
        // Vertical
        for(int x=0; x<101; x++){
            for(int y =0; y<100; y++){
                indices[i++] = y * 101 + x;
                indices[i++] = (y+1) * 101 + x;
            }
        }

        GLuint ibo;
        glCreateBuffers(1, &ibo);
        
        glVertexArrayElementBuffer(VAO, ibo);

        auto it = renderer->prepBuf((GLfloat*)v,sizeof(v));
        renderer->formatBuf(it, 3, {3}, *shader2);

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

    int numX = 50;
    int numY = 50;
    for(int x=0; x<numX; x++){
        for(int y=0; y<numY; y++){

        }
    }

    return 0;
}

#endif