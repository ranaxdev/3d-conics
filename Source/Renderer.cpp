#include "Renderer.h"

unsigned int Renderer::current_free_buf = -1; // Index into currently available buffer

void Renderer::enableAxis() {
    constexpr static const GLfloat axis_data[] = {
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

}

void Renderer::renderAxis() {

}

/*
GLuint Renderer::_prepBuf(const GLfloat *data) {
    current_free_buf++;
    glCreateBuffers(1, &buf[current_free_buf]);

    glNamedBufferStorage(buf[current_free_buf], sizeof(data), data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
}
*/