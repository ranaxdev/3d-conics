#ifndef _H_SPAWNER
#define _H_SPAWNER

#include "GUI.h"

class Spawner : public GUI{
public:
    Spawner();

    void update() override;

private:
    ImVec2 size;
    ImVec2 pos;
    bool state;
};

#endif