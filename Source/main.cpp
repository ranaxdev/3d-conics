#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>


#include "Harness.h"
#include "Shader.h"
#include "Camera.h"

#include "Utils/Math.h"
#include "Utils/Logger.h"
#include "Utils/Globals.h"

#define DEBUG 1
#define SHADER_SRC "/home/rana/Desktop/3Dconics/Shaders"

class App : public conics::Harness{
public:
    std::shared_ptr<Camera> camera;
    void startup() override {
        Shader* shader = new Shader(SHADER_SRC"/vert.glsl", SHADER_SRC"/frag.glsl");
        shader->bind();

        GLfloat data[] = {
                0.5f, 0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f
        };
        GLuint VAO, buffer;
        glCreateVertexArrays(1, &VAO);
        glCreateBuffers(1, &buffer);

        glNamedBufferStorage(buffer, sizeof(data), data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

        glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(VAO, 0, 0);
        glEnableVertexArrayAttrib(VAO, 0);

        glVertexArrayVertexBuffer(VAO, 0, buffer, 0, 3*sizeof(float));

        glBindVertexArray(VAO);
    }

    float delta = 0.0f;
    float last = 0.0f;
    void render(float currentTime) override {
        delta = currentTime - last;

        glUniformMatrix4fv(20, 1, GL_FALSE, &(camera->calc_VP(delta))[0][0]);
        glPointSize(40.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        last = currentTime;
    }
};

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
    //Vec<float, 3> v({23.0f, 2.0f, 1.0f, 4.0f, 6.0f});

    Logger::log(ERROR, "error occured", __FILENAME__, __LINE__);

    return 0;
}

#endif