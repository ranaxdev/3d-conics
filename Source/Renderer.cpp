#include <iostream>
#include "Renderer.h"

int Renderer::free_buf       = -1;
int Renderer::free_bindpoint = -1;

Renderer::Renderer(GLuint &VAO, GLuint *buf)
: VAO(VAO), buf(buf) {}


/*
 * Initialize axes data
 */
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
    GLuint loc = prepBuf((GLfloat*)axis_data, sizeof(axis_data));

    // Format data
    formatBuf(loc, 3, {0, 1}, Renderer::shader_axis);

}

void Renderer::test() {
    const GLfloat data2[] = {
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.23f, 0.0f,
            0.23f, 0.75f, 0.0f,
            -1.0f, -0.75f, 0.0f,
            0.73f, -0.40f, 0.0f,
            0.69f, 0.69f, 0.0f,
            1.0f, -0.88f, 0.0f
    };
    GLuint loc = prepBuf((GLfloat*)data2, sizeof(data2));
    formatBuf(loc, 3, {3}, Renderer::shader_gen);
}

/*
 * @data - Array of float data
 * @size - Size of the array in bytes
 * Inits a new buffer and returns its index
 */
unsigned int Renderer::prepBuf(GLfloat *data, GLuint size) {
    free_buf++;
    glCreateBuffers(1, &buf[free_buf]);
    glNamedBufferStorage(buf[free_buf], size, data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

    return free_buf;
}
unsigned int Renderer::prepBuf(GLushort *data, GLuint size) {
    free_buf++;
    glCreateBuffers(1, &buf[free_buf]);
    glNamedBufferStorage(buf[free_buf], size, data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

    return free_buf;
}


/*
 * @data - List of float data
 * Inits a new buffer and returns its index
 */
unsigned int Renderer::prepBuf(std::vector<GLfloat>& data) {
    int size = (int) data.size();
    int dat_size = 4*size;
    free_buf++;
    glCreateBuffers(1, &buf[free_buf]);
    glNamedBufferStorage(buf[free_buf], dat_size, nullptr, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

    float* ptr = (float*) glMapNamedBufferRange(buf[free_buf], 0, dat_size, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
    for(int i=0; i<size; i++){
        ptr[i] = data[i];
    }
    glUnmapNamedBuffer(buf[free_buf]);

    return free_buf;
}


/*
 * @loc                     - Active buffer location
 * @comps_per_elem          - Number of components in an element
 * @names                   - List of attribute names used in GLSL
 * @s                       - Shader to get the attribute names from
 *
 * Formats the buffer for the VAO
 */

void Renderer::formatBuf(GLuint loc, GLint comps_per_elem, std::vector<int> attribs, Shader& s) {
    free_bindpoint++;
    auto num_attribs = attribs.size();

    for(int i=0; i < num_attribs; i++){

        glVertexArrayAttribFormat(VAO, attribs[i], comps_per_elem, GL_FLOAT, GL_FALSE, (i*comps_per_elem)*sizeof(float));
        glVertexArrayAttribBinding(VAO, attribs[i], free_bindpoint);
        glEnableVertexArrayAttrib(VAO, attribs[i]);
    }

    glVertexArrayVertexBuffer(VAO, free_bindpoint, buf[loc], 0, (num_attribs*comps_per_elem)*sizeof(float));
}







