#ifndef _H_GUI_MENU
#define _H_GUI_MENU

#include "Surface.h"
#include "Globals.h"
#include "GUI.h"

class Menu : public GUI, public KeyListener{

public:
    Menu(float alpha, float beta, int lod, surface s);

    void update() override;

    void editToggled() override;

    surface s;
    float alpha, beta, amp, breath_timer;
    int lod;
    bool breathe;

    ImVec2 pos;
    ImVec2 size;
    const char* text_type;

};

#endif