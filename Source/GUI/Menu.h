#ifndef _H_GUI_MENU
#define _H_GUI_MENU

#include "GUI.h"

class Menu : public GUI{

public:
    Menu(float alpha, float beta, int lod);
    ~Menu() override = default;


    void update() override;

private:
    float alpha, beta, amp;
    int lod;
    bool breathe;

    ImVec2 pos;
    ImVec2 size;
};

#endif