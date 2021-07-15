#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Harness.h"
#include "Shader.h"

#define SHADER_SRC "/home/rana/Desktop/3Dconics/Shaders"
class App : public conics::Harness{

public:
    void startup() override {
        Shader* shader = new Shader(SHADER_SRC"/vert.glsl", SHADER_SRC"/frag.glsl");
        shader->bind();

        GLuint VAO;
        glCreateVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
    }

    void render(float currentTime) override {
        glPointSize(40.0f);
        glDrawArrays(GL_POINTS, 0, 1);
    }
};

int main(){
    App* a = new App;
    a->run(a);
    delete a;
    
    return 0;
}
