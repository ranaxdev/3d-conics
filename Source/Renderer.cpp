#include <string>
#include <iostream>
#include "Logger.h"
#include "Harness.h"
#include "Renderer.h"

// Static initializations
int Renderer::free_buf          = -1;
int Renderer::free_bindpoint    = -1;

Renderer::Renderer(GLuint &VAO, GLuint *buf)
: VAO(VAO), buf(buf) {
    // Buffers you want to pre-setup
    enableAxis();
}



/* ****************************************************************
 *                  RENDER-ABLES INITIALIZATIONS                  *
 ******************************************************************/
/*
 * Initialize axes data
 */
void Renderer::enableAxis() {
    const GLfloat axis_data[] = {
            // Axis 1 (red)
            0.0f, 0.0f, 2.5f,     1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -2.5f,    1.0f, 0.0f, 0.0f,
            // Axis 2 (green)
            0.0f, 2.5f, 0.0f,    0.0f, 1.0f, 0.0f,
            0.0f, -2.5f, 0.0f,   0.0f, 1.0f, 0.0f,
            // Axis 3 (blue)
            2.5f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
            -2.5f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    // Prepare buffer
    GLuint loc = prepBuf((GLfloat*)axis_data, sizeof(axis_data));

    // Format data
    formatBuf(loc, 3, {0, 1}, Renderer::shader_axis);

}




/* ****************************************************************
 *                        RENDERING ROUTINES                      *
 ******************************************************************/
void Renderer::renderGUI(Spawner &g) {
    g.update();
    if(g.enableAxis){
        renderAxis();
    }
    // New Mesh Generation
    if(g.mesh_generated){
        delete default_mesh->menu;
        delete default_mesh;
        default_mesh = new Mesh(g.current_surface, g.alpha, g.beta, g.t, g.lod);
    }
}


void Renderer::renderAxis() {
    glLineWidth(20.0f);
    shader_axis.bind();
    shader_axis.setMat4(20, conics::Harness::VP);

    glDrawArrays(GL_LINES , 0, 8);
}

/*
 * Renders vertical and horizontal components of mesh vertices
 */
void Renderer::renderMesh(Mesh& m) {
    // First time setup
    if(!m.first_update){
        GLuint loc = prepBuf(m.mesh_data, true);
        formatBuf(loc, 3, {3}, Renderer::shader_surface);
        m.saved_buffer = loc;
    }
    // Editing buffer otherwise (buffer changes after initial setup)
    m.update(); // IMPORTANT: UPDATE BEFORE EDIT, otherwise mesh breaks a bit
    if(m.first_update){
        // TODO: Optimization - Only call when actually editing properties
        editBuf(m.mesh_data, m.saved_buffer);
    }

    glLineWidth(10.0f);

    shader_surface.bind();
    shader_surface.setMat4(20, conics::Harness::VP);
    shader_surface.setMat4(21, m.model_transform);

    glm::vec3 color = glm::vec3(m.color[0], m.color[1], m.color[2]);
    shader_surface.setVec3(30, color);
    shader_surface.setInt(31, m.use_plain);

    int lod = (int) m.mesh_data.back(); // Retrieve reserved LOD

    /*
     * The vertical mesh data is appended to the horizontal one in the buffer
     * So to draw the vertical mesh, the starting index is half the size of the buffer
     * LOD is appended right at the end, it won't be used anyway because a vertex is 3 elements
     * Don't have to worry about alignment
     */
    for(int i=0; i<lod; i++){
        glDrawArrays(GL_LINE_STRIP, lod*i, lod); // Draw horizontal
        glDrawArrays(GL_LINE_STRIP, ((int) m.mesh_data.size()-1)/3/2+(lod*i), lod); // Draw vertical
    }
}






/* ****************************************************************
 *                      BUFFER SETUP ROUTINES                     *
 ******************************************************************/
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
unsigned int Renderer::prepBuf(std::vector<GLfloat>& data, bool big) {
    int size = (int) data.size();
    int dat_size = 4*size;

    // Either allocate a big buffer (for large meshes and such)
    // Or just as large as your data
    int to_allocate;
    if(big)
        to_allocate = ONE_MB;
    else
        to_allocate = dat_size;


    free_buf++;
    glCreateBuffers(1, &buf[free_buf]);
    glNamedBufferStorage(buf[free_buf], to_allocate, nullptr, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT); // 1mb buffer

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

    // Buffer overflowed
    if(dat_size >= ONE_MB){
        Logger::log(ERROR, "Buffer overflowed, buffer ID: "+ std::to_string(i), __FILENAME__);
    }

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





