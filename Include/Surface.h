#ifndef _H_SURFACE
#define _H_SURFACE

#include <vector>

enum surface{
    // Pure surfaces
    PARABOLOID=0,
    DISC,
    HYPERBOLIC,
    UNRESTRICTED_CONE,

    SEPARATOR,

    // Conic surfaces
    DOUBLE_CONE,
    CYLINDER,

    END
};

static const char* surface_names[] = {
        "PARABOLOID",
        "DISC",
        "HYPERBOLOID",
        "SURFACE CONE",
        "",
        "DOUBLE CONE",
        "CYLINDER",
        ""
};

#endif