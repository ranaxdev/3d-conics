#include <iostream>
#include "Renderer.h"
#include "Harness.h"

int Renderer::free_buf          = -1;
int Renderer::free_bindpoint    = -1;
GLuint Renderer::active_surface = -1;
bool Renderer::setup = false;
std::vector<GLfloat> Renderer::mesh_data = {};


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

/* Pre-fed mesh setup
 * Mesh properties (context-dependant):
 * @xrange - X values range e.g. if -5 to 5, enter 10
 * @yrange - Same as xrange but with y-vals. Note: this is z-axis in OpenGL
 * @angle  - Maximum angle range e.g. 360 for round mesh
 * @height - Maximum height range (along GL y-axis)
 * @lod    - Level of detail, how fine the mesh should be
 *
 * NOTE: A = x-range/height
 *       B = y-range/angle
 */
void Renderer::setupMesh(Mesh& m) {
    mesh_data.clear();

    // Create horizontal and vertical meshes
    float split = m.lod/2;
    for(int i=0; i<m.lod; i++){
        for(int j=0; j<m.lod; j++){
            float A = m.alpha*(((float) (i-split))/split);
            float B = m.beta*(((float) (j-split))/split);
            Vertex3D v = func(A,B, m.time, m.s); // Solve surface eq
            mesh_data.push_back(v.x);
            mesh_data.push_back(v.z);
            mesh_data.push_back(-2.5f+v.y); // Move to center
        }
    }
    for(int i=0; i<m.lod; i++){
        for(int j=0; j<m.lod; j++){
            float x = m.alpha*(((float) (j-split))/split); // swap i,j for other dir.
            float y = m.beta*(((float) (i-split))/split);
            Vertex3D v = func(x,y,m.time,m.s);
            mesh_data.push_back(v.x);
            mesh_data.push_back(v.z);
            mesh_data.push_back(-2.5f+v.y);
        }
    }
    // Reserve LOD for drawing
    mesh_data.push_back((float) m.lod);

    // First time setup
    if(!Renderer::setup){
        GLuint loc = prepBuf(mesh_data);
        formatBuf(loc, 3, {3}, Renderer::shader_surface);
        Renderer::active_surface = loc;
    }
    // Editing buffer otherwise
    else{
        editBuf(mesh_data, Renderer::active_surface);
    }

    Renderer::setup = true;

}


/* Rendering routines */
void Renderer::renderAxis() {
    glLineWidth(20.0f);
    shader_axis.bind();
    shader_axis.setMat4(20, conics::Harness::VP);

    glDrawArrays(GL_LINES , 0, 8);
}

/*
 * Renders vertical and horizontal components of mesh vertices
 */
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
Vertex3D Renderer::func(float A, float B, float t, surface s) {
    Vertex3D v{};
    switch (s) {
        /* SURFACES */
        case PARABOLOID:
            v.x = A;
            v.y = B;
            v.z = pow(A,2) + pow(B,2);
            break;

        case DISC:
            v.x = A;
            v.y = B;
            v.z = sin(pow(A,2) + pow(B,2));
            break;

        case HYPERBOLIC:
            v.x = A;
            v.y = B;
            v.z = pow(A,2) - pow(B,2);
            break;

        case UNRESTRICTED_CONE:
            v.x = A;
            v.y = B;
            v.z = sqrt(pow(A,2)+pow(B,2));
            break;

        /* CONICS */
        case DOUBLE_CONE:
            v.x = A*cos(B);
            v.y = A*sin(B);
            v.z = A;
            break;
    }
    return v;
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
 * @buf - Buffer to edit
 * Edits buffer data
 */
unsigned int Renderer::editBuf(std::vector<GLfloat>& data, GLuint i) {
    int size = (int) data.size();
    int dat_size = 4*size;

    float* ptr = (float*) glMapNamedBufferRange(buf[i], 0, dat_size, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);
    for(int x=0; x<size; x++){
        ptr[x] = data[x];
    }
    glUnmapNamedBuffer(buf[i]);

    return i;
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




