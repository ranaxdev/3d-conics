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
    bool isConic{};
    const char* text_alpha, *text_beta;
    int lod; float alpha, beta, t;
    float MIN_ALPHA, MAX_ALPHA, MIN_BETA, MAX_BETA;
    surface current_surface;

    bool mesh_items_selected[END+1] = {false};
    bool mesh_generated;

private:
    void disableExcept(int i);
    int findActive();

protected:
    int load_mesh_config_callback(int argc, char **argv, char **azColName) override;
};

#endif