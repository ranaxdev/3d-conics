#include "Renderer.h"



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


    glNamedBufferStorage(buf[0], sizeof(axis_data), axis_data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

    // Position
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glEnableVertexArrayAttrib(VAO, 0);
    // Color
    glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float));
    glVertexArrayAttribBinding(VAO, 1, 0);
    glEnableVertexArrayAttrib(VAO, 1);

    glVertexArrayVertexBuffer(VAO, 0, buf[0], 0, 6*sizeof(float));

}

