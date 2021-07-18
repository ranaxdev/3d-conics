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


class App : public conics::Harness{
public:
    std::shared_ptr<Camera> camera;
    void startup() override {
        Shader* shader = new Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");

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
        GLuint VAO, buffer;
        glCreateVertexArrays(1, &VAO);
        glCreateBuffers(1, &buffer);

        glNamedBufferStorage(buffer, sizeof(data), data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

        // Position
        glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(VAO, 0, 0);
        glEnableVertexArrayAttrib(VAO, 0);
        // Color
        glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float));
        glVertexArrayAttribBinding(VAO, 1, 0);
        glEnableVertexArrayAttrib(VAO, 1);

        glVertexArrayVertexBuffer(VAO, 0, buffer, 0, 6*sizeof(float));

        glBindVertexArray(VAO);
    }

    float delta = 0.0f;
    float last = 0.0f;
    void render(float currentTime) override {
        delta = currentTime - last;

        glUniformMatrix4fv(20, 1, GL_FALSE, &(camera->calc_VP(delta))[0][0]);
        glPointSize(40.0f);
        glLineWidth(40.0f);
        glDrawArrays(GL_LINES , 0, 8);

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
    std::cout << SRC;
    return 0;
}

#endif