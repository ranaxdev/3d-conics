#include <iostream>
#include "Renderer.h"

int Renderer::free_buf       = -1;
int Renderer::free_attrib    = -1;
int Renderer::free_bindpoint = -1;

Renderer::Renderer(GLuint &VAO, GLuint *buf)
: VAO(VAO), buf(buf) {}


void Renderer::enableAxis() {
    const GLfloat axis_data[] = {
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

    // Prepare buffer
    GLuint loc = _prepBuf((GLfloat*)axis_data, sizeof(axis_data));

    // Format data
    _formatBuf(loc, 2, 3, {"position", "color"}, Renderer::shader_axis);

}

unsigned int Renderer::_prepBuf(GLfloat *data, GLuint size) {
    free_buf++;
    glCreateBuffers(1, &buf[free_buf]);

    glNamedBufferStorage(buf[free_buf], size, data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

    return free_buf;
}

void Renderer::_formatBuf(GLuint loc, GLuint num_attribs, GLint comps_per_elem, std::vector<const char*> names, Shader& s) {
    free_bindpoint++;

    for(int i=0; i < num_attribs; i++){
        GLuint attrib_loc = s.get_attrib_loc(names[i]);
        glVertexArrayAttribFormat(VAO, attrib_loc, comps_per_elem, GL_FLOAT, GL_FALSE, (i*comps_per_elem)*sizeof(float));
        glVertexArrayAttribBinding(VAO, attrib_loc, free_bindpoint);
        glEnableVertexArrayAttrib(VAO, attrib_loc);
    }

    glVertexArrayVertexBuffer(VAO, free_bindpoint, buf[loc], 0, (num_attribs*comps_per_elem)*sizeof(float));
}



