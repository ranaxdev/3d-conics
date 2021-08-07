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
    void setupParaboloid(float xrange, float yrange, int lod);

    void renderAxis(Shader& s);
    void renderParaboloid(Shader& s);

    unsigned int prepBuf(GLfloat data[], GLuint size);
    unsigned int prepBuf(GLushort data[], GLuint size); // Temp: make this generic later
    unsigned int prepBuf(std::vector<GLfloat>& data);

    void formatBuf(GLuint loc, GLint comps_per_elem, std::vector<int> attribs, Shader& s);

    // Shaders
    Shader shader_axis = Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");
    Shader shader_gen = Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");
private:

    static int free_buf;
    static int free_bindpoint;
    GLuint VAO;

    GLuint* buf;

    // Surface data
    std::vector<GLfloat> data_paraboloid;


    // Colors
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

};
#endif