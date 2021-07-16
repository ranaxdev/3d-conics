#ifndef _H_KEYLISTENER
#define _H_KEYLISTENER
#include <GLFW/glfw3.h>

class KeyListener{
public:
    virtual const int& pressed(const int& keycode) const;
};

#endif