#ifndef _H_RENDERER
#define _H_RENDERER
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/Globals.h"
#include "Shader.h"

class Renderer{
public:
    Renderer() = delete;
    ~Renderer() = default;

    static void enableAxis();
    static void renderAxis();

private:
    // Axis parts
    Shader* axis_shader = new Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");

    // Memory utils
    static unsigned int current_free_buf;
    GLuint buf[1024];
    

};
#endif