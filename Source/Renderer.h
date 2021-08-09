#ifndef _H_RENDERER
#define _H_RENDERER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Utils/Globals.h"
#include "Shader.h"

enum surface{
    // Pure surfaces
    PARABOLOID,
    DISC,
    HYPERBOLIC,
    UNRESTRICTED_CONE,

    // Conic surfaces
    DOUBLE_CONE = 20,
};

struct Mesh{
    // alpha - x-range/height depending on surface type
    // beta  - y-range/angle depending on surface type
    float alpha, beta, time;
    int lod;
    surface s;

    Mesh(surface s, float alpha, float beta, float time=1.0f, int lod=10)
    : s(s), alpha(alpha), beta(beta), time(time), lod(lod)
    {}
};

struct Vertex3D{
    float x,y,z;
};

class Renderer{
public:
    Renderer(GLuint& VAO, GLuint buf[]);
    ~Renderer() = default;

    void enableAxis();
    void updateMesh(Mesh& m);

    void renderAxis();
    void renderMesh(std::vector<GLfloat>& data);

    unsigned int prepBuf(GLfloat data[], GLuint size);
    unsigned int prepBuf(GLushort data[], GLuint size);
    unsigned int prepBuf(std::vector<GLfloat>& data, bool big);
    unsigned int editBuf(std::vector<GLfloat>& data, GLuint i);

    void formatBuf(GLuint loc, GLint comps_per_elem, std::vector<int> attribs, Shader& s);

    // Current active mesh vertices
    static std::vector<GLfloat> mesh_data;

private:
    // Memory mgmt
    static int free_buf;
    static int free_bindpoint;
    GLuint VAO;
    GLuint* buf;

    // State
    static bool mesh_setup;              // Mesh buffer has been setup before
    static GLuint active_surface;        // Buffer ID/loc for currently active surface

    // Util
    Vertex3D func(float A, float B, float t, surface s); // Surface/Conics eq solver

    // Shaders
    Shader shader_axis = Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");
    Shader shader_surface = Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");

    // Colors
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

};
#endif