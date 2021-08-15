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