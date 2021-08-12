#ifndef _H_SPAWNER
#define _H_SPAWNER

#include "Surface.h"
#include "GUI.h"

class Spawner : public GUI{
public:
    Spawner();

    void update() override;

    ImVec2 size;
    ImVec2 pos;
    bool enableAxis;

    bool mesh_items_selected[END+1] = {false};

private:
    void disableExcept(int i);
};

#endif