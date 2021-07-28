#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>


#include "Harness.h"
#include "Shader.h"
#include "Camera.h"

#include "Utils/Math.h"
#include "Utils/Logger.h"
#include "Utils/Globals.h"


class App : public conics::Harness{
public:
    std::shared_ptr<Camera> camera;
    Shader* shader;
    Shader* shader2;

    // Colors
    glm::vec4 c1 = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

    // Indexed drawing stuff
    int size =0;

    void startup() override {
        shader = new Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");
        shader2 = new Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");

        shader->bind();

        GLfloat data[] = {
                // Axis 1 (red)
                0.0f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, -5.0f,    1.0f, 0.0f, 0.0f,

                // Axis 2 (green)
                0.0f, 2.5f, -2.5f,    0.0f, 1.0f, 0.0f,
                0.0f, -2.5f, -2.5f,   0.0f, 1.0f, 0.0f,

                // Axis 3 (blue)
                2.5f, 0.0f, -2.5f,    0.0f, 0.0f, 1.0f,
                -2.5f, 0.0f, -2.5f,   0.0f, 0.0f, 1.0f
        };
        std::vector<float> data2 = {
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.23f, 0.75f, 0.0f,
                -1.0f, -0.75f, 0.0f,
                -0.5f, 0.23f, 0.0f
        };
        size = (int) data2.size();
        int dat_size = 4*size;

        GLuint VAO;
        GLuint buffer[2];
        glCreateVertexArrays(1, &VAO);
        glCreateBuffers(2, buffer);

        /* Axis data */
        glNamedBufferStorage(buffer[0], sizeof(data), data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

        // Position
        glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(VAO, 0, 0);
        glEnableVertexArrayAttrib(VAO, 0);
        // Color
        glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float));
        glVertexArrayAttribBinding(VAO, 1, 0);
        glEnableVertexArrayAttrib(VAO, 1);

        glVertexArrayVertexBuffer(VAO, 0, buffer[0], 0, 6*sizeof(float));

        /* Other data */
        glNamedBufferStorage(buffer[1], dat_size, nullptr, GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
        float* ptr = (float*) glMapNamedBufferRange(buffer[1], 0, dat_size, GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
        for(int i=0; i<size; i++){
            ptr[i] = data2[i];
        }
        glUnmapNamedBuffer(buffer[1]);

        glVertexArrayAttribFormat(VAO, 3, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(VAO, 3, 1);
        glEnableVertexArrayAttrib(VAO, 3);

        glVertexArrayVertexBuffer(VAO, 1, buffer[1], 0, 3*sizeof(float));


        glBindVertexArray(VAO);
    }

    float delta = 0.0f;
    float last = 0.0f;
    void render(float currentTime) override {
        delta = currentTime - last;


        glPointSize(20.0f);
        glLineWidth(40.0f);


        shader2->bind();
        shader2->setMat4(20, camera->calc_VP(delta));
        shader2->setVec4(30, c1);
        glDrawArrays(GL_POINTS, 0, size);

        shader->bind();
        shader->setMat4(20, camera->calc_VP(delta));
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
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float angle = 0.0f;
    std::vector<float> v;
    std::vector<float> dat;
    dat.push_back(55);
    dat.push_back(27);
    dat.push_back(69);
    std::cout << dat[0] << " " << dat[1] << " " << dat[2] << std::endl;
    for(int i=0; i < 5; i++){
        z = (float)i;
        for(int a=0; a<360; a++){
            x = (float) (sqrt(z) * cos(glm::radians((float)a)));
            y = (float) (sqrt(z) * sin(glm::radians((float)a)));
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            //printf("%4.4ff, %4.4ff, %4.4ff,\n",x,y,z);


        }
    }

    return 0;
}

#endif