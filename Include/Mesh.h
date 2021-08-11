#ifndef _H_MESH
#define _H_MESH

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <memory>
#include <vector>
#include "Menu.h"

enum surface{
    // Pure surfaces
    PARABOLOID,
    DISC,
    HYPERBOLIC,
    UNRESTRICTED_CONE,

    // Conic surfaces
    DOUBLE_CONE = 20,
};

struct Vertex3D{
    float x,y,z;
};

class Mesh{
public:
    Mesh(surface s, float alpha, float beta, float time=1.0f, int lod=10);
    ~Mesh();

    bool first_update;
    GLuint saved_buffer;
    std::vector<GLfloat> mesh_data; // Contain all mesh vertices

    void setAlpha(float alpha);
    void update();

     std::shared_ptr<Menu> menu; // GUI
private:
    // alpha - x-range/height depending on surface type
    // beta  - y-range/angle depending on surface type
    float alpha, beta, time;
    int lod;

    surface s;
    Vertex3D func(float A, float B, float t, surface s); // Surface/Conics eq solver

};

#endif