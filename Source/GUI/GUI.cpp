#include <algorithm>
#include <iostream>
#include "GUI.h"

bool GUI::state = true;
// Add list of window flags
void GUI::addFlags(std::vector<ImGuiWindowFlags_>&& flags) {
    for(auto f : flags){
        GUI::flag_list.push_back(f);
    }
    GUI::updateFlags();
}

// Remove list of window flags
void GUI::removeFlags(std::vector<ImGuiWindowFlags_>&& flags) {
    // Remove subset of flags (toRemove) from menu flag list
    std::sort(flags.begin(), flags.end());
    GUI::flag_list.erase(
            std::remove_if(GUI::flag_list.begin(), GUI::flag_list.end(),
                           [&](auto x){return std::binary_search(flags.begin(), flags.end(),x);})
                           , GUI::flag_list.end());

    GUI::updateFlags();
}


// Update window flags from flags in the flag list vector (call after changing flags)
void GUI::updateFlags() {
    GUI::flags = ImGuiWindowFlags_None;
    std::sort(GUI::flag_list.begin(), GUI::flag_list.end());

    for(auto& f : GUI::flag_list){
        GUI::flags = static_cast<ImGuiWindowFlags_>(GUI::flags | f);
    }
}

GUI::GUI() {
    style->Colors[ImGuiCol_TitleBgActive] = dblue;
    style->Colors[ImGuiCol_TitleBg] = dblue;
}

void GUI::load_mesh_config(surface s) {
    int surface_ID = (int)s+1;

    sqlite3* db;
    char* err = nullptr;
    int rc;

    rc = sqlite3_open((SRC+"surfaceDB.sqlite").c_str(), &db);

    if(rc){
        Logger::log(ERROR, "Database not opened.", __FILENAME__);
        Logger::log(ERROR, sqlite3_errmsg(db), __FILENAME__);
    }
    else{
        Logger::log(INFO, "Database opened successfully", __FILENAME__);
    }
    std::string str = "SELECT * FROM surface WHERE surface_ID="+std::to_string(surface_ID)+";";
    const char* sql = str.c_str();

    rc = sqlite3_exec(db, sql, HELPER_load_mesh_config_callback, this, &err);

    if (rc != SQLITE_OK){
        Logger::log(ERROR, "Query failed", __FILENAME__);
        sqlite3_free(err);
    }
    else{
        Logger::log(INFO, "Queried successfully", __FILENAME__);
    }
    sqlite3_close(db);
}

int GUI::HELPER_load_mesh_config_callback(void *objPtr, int argc, char **argv, char **azColName) {
    return ((GUI*)objPtr)->load_mesh_config_callback(argc, argv, azColName);
}

GUI::~GUI() = default;



