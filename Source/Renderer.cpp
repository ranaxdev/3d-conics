#include <iostream>
#include "Renderer.h"
#include "Harness.h"

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
/* Pre-fed surfaces setups */

/*
 * @xrange - X values range e.g. if -5 to 5, enter 10
 * @yrange - Same as xrange but with y-vals. Note: this is z-axis in OpenGL
 * @lod    - Level of detail, how fine the mesh should be
 */
void Renderer::setupSurface(float xrange, float yrange, int lod, float time, surface type) {
    surface_data.clear();

    // Create horizontal and vertical meshes
    float split = lod/2;
    for(int i=0; i<lod; i++){
        for(int j=0; j<lod; j++){
            float x = xrange*(((float) (i-split))/split);
            float y = yrange*(((float) (j-split))/split);
            float z = func(x,y, time, type); // Solve surface eq
            surface_data.push_back(x);
            surface_data.push_back(z);
            surface_data.push_back(-2.5f+y); // Move to center
        }
    }
    for(int i=0; i<lod; i++){
        for(int j=0; j<lod; j++){
            float x = xrange*(((float) (j-split))/split); // swap i,j for other dir.
            float y = yrange*(((float) (i-split))/split);
            float z = func(x,y,time,type);
            surface_data.push_back(x);
            surface_data.push_back(z);
            surface_data.push_back(-2.5f+y);
        }
    }
    // Reserve LOD for drawing
    surface_data.push_back((float) lod);


    GLuint loc = prepBuf(surface_data);
    formatBuf(loc, 3, {3}, Renderer::shader_surface);

}

/*
 * @max_height - h-values range
 * @max_angle  - Same as max_height but with angles
 * @lod        - Level of detail, how fine the mesh should be
 */
void Renderer::setupConic(float max_height, float max_angle, int lod, float time, conic type) {
    conic_data.clear();

    // Create horizontal and vertical meshes
    float split = lod/2;
    for(int i=0; i<lod; i++){
        for(int j=0; j<lod; j++){
            float h = max_height*(((float) (i-split))/split);
            float a = max_angle*(((float) (j-split))/split);
            float x = h*cos(a);
            float y = h*sin(a);
            conic_data.push_back(x);
            conic_data.push_back(h);
            conic_data.push_back(-2.5f+y); // Move to center
        }
    }
    for(int i=0; i<lod; i++){
        for(int j=0; j<lod; j++){
            float h = max_height*(((float) (j-split))/split);
            float a = max_angle*(((float) (i-split))/split);
            float x = h*cos(a);
            float y = h*sin(a);
            conic_data.push_back(x);
            conic_data.push_back(h);
            conic_data.push_back(-2.5f+y);
        }
    }

    // Reserve LOD for drawing
    conic_data.push_back((float) lod);

    GLuint loc = prepBuf(conic_data);
    formatBuf(loc, 3, {3}, Renderer::shader_surface);
}



/* Rendering routines */
void Renderer::renderAxis() {
    glLineWidth(20.0f);
    shader_axis.bind();
    shader_axis.setMat4(20, conics::Harness::VP);

    glDrawArrays(GL_LINES , 0, 8);
}


void Renderer::renderMesh(std::vector<GLfloat>& data) {
    glLineWidth(10.0f);

    shader_surface.bind();
    shader_surface.setMat4(20, conics::Harness::VP);
    shader_surface.setVec4(30, cyan);

    int lod = (int) data.back();

    /*
     * The vertical mesh data is appended to the horizontal one in the buffer
     * So to draw the vertical mesh, the starting index is half the size of the buffer
     * LOD is appended right at the end, it won't be used anyway because a vertex is 3 elements
     * Don't have to worry about alignment
     */
    for(int i=0; i<lod; i++){
        glDrawArrays(GL_LINE_STRIP, lod*i, lod); // Draw horizontal
        glDrawArrays(GL_LINE_STRIP, ((int) data.size()-1)/3/2+(lod*i), lod); // Draw vertical
    }
}

/*
 * Solves surface equation of the type provided
 * Time parameter is optional (some surfaces don't use it)
 */
float Renderer::func(float x, float y, float t, surface type) {
    float z = 0.0f;
    switch (type) {
        case PARABOLOID:
            z = pow(x,2) + pow(y,2);
            break;

        case DISC:
            z = sin(pow(x,2) + pow(y,2));
            break;

        case HYPERBOLIC:
            z = pow(x,2) - pow(y,2);
            break;

        case UNRESTRICTED_CONE:
            z = sqrt(pow(x,2)+pow(y,2));
            break;
    }
    return z;
}

/*
 * Solves conics equation of the type provided
 */
float Renderer::func2(float h, float a, float t, conic type) {
    switch (type) {
        case CONE:
            break;
    }
    return 0;
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


