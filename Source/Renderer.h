#ifndef _H_RENDERER
#define _H_RENDERER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Utils/Globals.h"
#include "Shader.h"

enum surface{
    PARABOLOID,
    DISC,
    HYPERBOLIC,
    UNRESTRICTED_CONE
};
enum conic{
    DOUBLE_CONE
};

struct Vertex3D{
    float x,y,z;
};

class Renderer{
public:
    Renderer(GLuint& VAO, GLuint buf[]);
    ~Renderer() = default;

    void enableAxis();
    void setupSurface(float xrange, float yrange, int lod, float time, surface type);
    void setupConic(float max_height, float max_angle, int lod, float time, conic type);

    void renderAxis();
    void renderMesh(std::vector<GLfloat>& data);

    unsigned int prepBuf(GLfloat data[], GLuint size);
    unsigned int prepBuf(GLushort data[], GLuint size); // Temp: make this generic later
    unsigned int prepBuf(std::vector<GLfloat>& data);
    unsigned int editBuf(std::vector<GLfloat>& data, GLuint i);

    void formatBuf(GLuint loc, GLint comps_per_elem, std::vector<int> attribs, Shader& s);

    // Current active mesh vertices
    static std::vector<GLfloat> surface_data;
    static std::vector<GLfloat> conic_data;

private:
    // Memory mgmt
    static int free_buf;
    static int free_bindpoint;
    static bool setup;
    static GLuint active_surface;
    static GLuint active_conic;
    GLuint VAO;
    GLuint* buf;

    // Util
    float func(float x, float y, float t, surface type); // Surface eq solver
    Vertex3D func2(float h, float a, float t, conic type); // Conic eq solver

    // Shaders
    Shader shader_axis = Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");
    Shader shader_surface = Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");

    // Colors
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

};
#endif