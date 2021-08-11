#ifndef _H_SURFACE
#define _H_SURFACE

#include <vector>

enum surface{
    // Pure surfaces
    PARABOLOID,
    DISC,
    HYPERBOLIC,
    UNRESTRICTED_CONE,

    SEPARATOR,

    // Conic surfaces
    DOUBLE_CONE
};

static const char* surface_names[] = {
        "PARABOLOID",
        "DISC",
        "HYPERBOLOID",
        "SURFACE CONE",
        "",
        "DOUBLE CONE"
};

#endif