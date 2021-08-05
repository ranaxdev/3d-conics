#ifndef _H_RENDERER
#define _H_RENDERER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Utils/Globals.h"
#include "Shader.h"

class Renderer{
public:
    Renderer(GLuint& VAO, GLuint buf[]);
    ~Renderer() = default;

    void enableAxis();

private:
    static int free_buf;
    static int free_attrib;
    static int free_bindpoint;
    GLuint VAO;
    GLuint* buf;

    unsigned int _prepBuf(GLfloat data[], GLuint size);
    void _formatBuf(GLuint loc, GLuint num_attribs, GLint comps_per_elem, std::vector<const char*> names, Shader& s);

    // Shaders
    Shader shader_axis = Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");
};
#endif