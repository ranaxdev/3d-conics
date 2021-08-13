#include <cmath>
#include "Mesh.h"

Mesh::Mesh(surface s, float alpha, float beta, float time, int lod)
: s(s), alpha(alpha), beta(beta), time(time), lod(lod)
{
    Mesh::first_update = false;
    Mesh::saved_buffer = INT16_MAX;

    isConic = false;
    if(s > SEPARATOR)
        isConic = true;

    Mesh::model_transform = glm::mat4(1.0f);
    Mesh::origin = glm::vec3(0.0f, 0.0f, -2.5f);
    Mesh::menu = new Menu(alpha, beta, lod, isConic, s);
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
void Mesh::update() {
    menu->update(); // Render GUI
    alpha = menu->alpha;
    beta = menu->beta;
    lod = menu->lod;

    mesh_data.clear();
    // Create horizontal and vertical meshes
    float split = lod/2;
    for(int i=0; i<lod; i++){
        for(int j=0; j<lod; j++){
            float A = alpha*(((float) (i-split))/split);
            float B = beta*(((float) (j-split))/split);
            Vertex3D v = func(A,B, time, s); // Solve surface eq
            mesh_data.push_back(v.x);
            mesh_data.push_back(v.z);
            mesh_data.push_back(v.y); // Move to center
        }
    }
    for(int i=0; i<lod; i++){
        for(int j=0; j<lod; j++){
            float x = alpha*(((float) (j-split))/split); // swap i,j for other dir.
            float y = beta*(((float) (i-split))/split);
            Vertex3D v = func(x,y,time,s);
            mesh_data.push_back(v.x);
            mesh_data.push_back(v.z);
            mesh_data.push_back(v.y);
        }
    }

    // Transformations
    model_transform = glm::mat4(1.0f);
    model_transform = glm::rotate(model_transform, menu->x_trans, glm::vec3(1.0f, 0.0f, 0.0f));
    model_transform = glm::rotate(model_transform, menu->y_trans, glm::vec3(0.0f, 1.0f, 0.0f));
    model_transform = glm::rotate(model_transform, menu->z_trans, glm::vec3(0.0f, 0.0f, 1.0f));


    // Reserve LOD to inform rendering of this mesh
    mesh_data.push_back((float) lod);

    // First time setup complete
    if(!Mesh::first_update)
        Mesh::first_update = true;

}


/*
 * Solves surface/conic equation of the type provided
 * Time parameter is optional (some surfaces don't use it)
 */
Vertex3D Mesh::func(float A, float B, float t, surface s) {
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

Mesh::~Mesh() = default;



