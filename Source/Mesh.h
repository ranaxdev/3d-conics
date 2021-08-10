#ifndef _H_MESH
#define _H_MESH

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "GUI/Menu.h"

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
    ~Mesh() = delete;

    bool first_update;
    GLuint saved_buffer;
    std::vector<GLfloat> mesh_data; // Contain all mesh vertices

    void setAlpha(float alpha);
    void update();
private:
    // alpha - x-range/height depending on surface type
    // beta  - y-range/angle depending on surface type
    float alpha, beta, time;
    int lod;

    Menu* menu;

    surface s;
    Vertex3D func(float A, float B, float t, surface s); // Surface/Conics eq solver

};

#endif