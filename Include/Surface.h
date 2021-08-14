#ifndef _H_SURFACE
#define _H_SURFACE

#include <vector>

struct Surface_Config{
    // Main
    float alpha, beta, amplitude, t;
    float max_alpha, min_alpha, max_beta, min_beta;
    const char* text_alpha, *text_beta, *text_type, *text_mesh;
    int lod;
    bool isConic;

    // Breathe functionality
    bool breathe_btn;
    float breathe_alpha_lim, breath_beta_lim;
    float breathe_timer;

    // Transform functionality
    bool x_rot_btn, y_rot_btn, z_rot_btn;
    float x_rot, y_rot, z_rot;
    float x_rot_timer, y_rot_timer, z_rot_timer;

    // Color controls
    bool plain;
    float color[3];
};

enum surface{
    // Pure surfaces
    PARABOLOID=0,
    DISC,
    HYPERBOLIC,
    UNRESTRICTED_CONE,
    DNA,
    SOMBRERO,

    SEPARATOR,

    // Conic surfaces
    TORUS,
    DOUBLE_CONE,
    SINGLE_CONE,
    SPHERE,
    CYLINDER,

    END
};

static const char* surface_names[] = {
        "PARABOLOID",
        "DISC",
        "HYPERBOLIC PARABOLOID",
        "SURFACE CONE",
        "DNA",
        "SOMBRERO",
        "",
        "TORUS",
        "DOUBLE CONE",
        "SINGLE CONE",
        "SPHERE",
        "CYLINDER",
        ""
};

#endif