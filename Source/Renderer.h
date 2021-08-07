#ifndef _H_RENDERER
#define _H_RENDERER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Utils/Globals.h"
#include "Shader.h"

enum surface{
    PARABOLOID
};

class Renderer{
public:
    Renderer(GLuint& VAO, GLuint buf[]);
    ~Renderer() = default;

    void enableAxis();
    void setupSurface(float xrange, float yrange, int lod, float time, surface type);

    void renderAxis();
    void renderParaboloid();

    unsigned int prepBuf(GLfloat data[], GLuint size);
    unsigned int prepBuf(GLushort data[], GLuint size); // Temp: make this generic later
    unsigned int prepBuf(std::vector<GLfloat>& data);

    void formatBuf(GLuint loc, GLint comps_per_elem, std::vector<int> attribs, Shader& s);

private:
    // Memory mgmt
    static int free_buf;
    static int free_bindpoint;
    GLuint VAO;
    GLuint* buf;

    // Util
    float func(float x, float y, float t, surface type); // Surface eq solver

    // Shaders
    Shader shader_axis = Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");
    Shader shader_surface = Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");

    // Currently active surface's vertices
    std::vector<GLfloat> surface_data;

    // Colors
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

};
#endif