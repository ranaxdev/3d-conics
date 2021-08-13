#ifndef _H_SURFACE
#define _H_SURFACE

#include <vector>

enum surface{
    // Pure surfaces
    PARABOLOID=0,
    DISC,
    HYPERBOLIC,
    UNRESTRICTED_CONE,
    DNA,
    TORUS,
    SOMBRERO,

    SEPARATOR,

    // Conic surfaces
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
        "TORUS",
        "SOMBRERO",
        "",
        "DOUBLE CONE",
        "SINGLE CONE",
        "SPHERE",
        "CYLINDER",
        ""
};

#endif