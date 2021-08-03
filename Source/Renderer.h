#ifndef _H_RENDERER
#define _H_RENDERER
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    unsigned int _prepBuf(GLfloat data[], unsigned int size);
    void _formatBuf(GLuint loc, unsigned int num_attribs, );
};
#endif