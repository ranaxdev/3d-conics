#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Utils/Globals.h"
#include "Utils/Logger.h"
#include "Harness.h"

/**************************************************************************
 *                                   GUI
 ************************************************************************* */
/* GENERAL */

/* MENU */
ImVec2 conics::Harness::menu_pos = ImVec2(0.0f, 0.0f);
ImVec2 conics::Harness::menu_size = ImVec2(320.0f, 100.0f);
int conics::Harness::menu_lod = 5.0f;

// Menu Window
void conics::Harness::show_menu() {
    ImGui::SetNextWindowPos(menu_pos);
    ImGui::SetNextWindowSize(menu_size);

    ImGui::Begin("Control Menu", nullptr,
                 // Menu window properties
                 ImGuiWindowFlags_NoResize);

    ImGui::SliderInt("   LOD", &conics::Harness::menu_lod, 5.0f, MAX_LOD);
    ImGui::End();
}


/**************************************************************************
 *                          CONICS ROUTINES HARNESS
 ************************************************************************* */
glm::mat4 conics::Harness::VP = glm::mat4(1.0f);

conics::Harness::~Harness() {
    // Dump log file
    Logger::dump();
}

void conics::Harness::run(conics::Harness* h) {
    // GLFW init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window
    window = glfwCreateWindow(w.width, w.height, w.title, nullptr, nullptr);
    if(window == nullptr){
        Logger::log(ERROR, "Could not create GLFW window", __FILENAME__);
        glfwTerminate();
    }
    // Window settings
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, (void*)(this)); // Pointer to app window that implements this harness
    // GLFW settings
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Callbacks
    glfwSetKeyCallback(window, conics::key_callback);

    // Load GLAD
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Logger::log(ERROR, "Could not load GLAD", __FILENAME__);
        glfwTerminate();
    }

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glViewport(0,0,1920,1080);

    /* Application Initialization */
    glCreateVertexArrays(1, &VAO);
    Harness::R = new Renderer(Harness::VAO, Harness::buf); // Renderer instance
    IMGUI_CHECKVERSION();

    // imGUI initialization
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF((FONT_ROBOTO).c_str(), 20);
    (void)io;


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    startup();

    glBindVertexArray(VAO);


    // Application Rendering
    const GLfloat screen_color[4] = {w.color[0], w.color[1], w.color[2], w.color[3]};
    const float one = 1.0f;
    while(!glfwWindowShouldClose(window)){
        glClearBufferfv(GL_COLOR, 0, screen_color);
        glClearBufferfv(GL_DEPTH, 0, &one);

        // Update observers
        for(auto& o : conics::Harness::keylisteners){
            // NOTE: for key callback (NOT poll) => o->keys[currentKey] = currentAction
            // Poll tracked keys for presses & mouse positions
            for(auto& k : keys_to_poll){
                if(glfwGetKey(window, k) == GLFW_PRESS)
                    o->keys[k] = 1;
                else
                    o->keys[k] = 0;

                // Send current cursor position
                glfwGetCursorPos(window, &o->xpos, &o->ypos);

                // Send editing state
                o->editing = Harness::editing;
            }
        }

        // GUI Rendering frame initialization
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render application
        render((float) glfwGetTime());

        // Render GUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}




void conics::Harness::startup() {}

void conics::Harness::render(float currentTime) {}

void conics::Harness::setWindow(const conics::Window &window) {
    conics::Harness::w = window;
}

const conics::Window& conics::Harness::getWindow() const {
    return Harness::w;
}

void conics::Harness::addKeyListener(const std::shared_ptr<KeyListener>& k) {
    Harness::keylisteners.push_back(k);
}

void conics::Harness::setKA(const int &key, const int &action) {
    Harness::currentKey = key;
    Harness::currentAction = action;
}

void conics::Harness::toggleEditing() {
    Harness::editing = !Harness::editing;
}

const bool conics::Harness::isEditing() const {
    return Harness::editing;
}


/**************************************************************************
 *                          CONICS ROUTINES GENERAL
 ************************************************************************* */
void conics::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Retrieve harness of current window
    Harness* instance = (Harness*)glfwGetWindowUserPointer(window);

    // Send key info to application that implements the harness
    if(instance){
        instance->setKA(key, action);
    }

    // Shutdown
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);


    // Toggle Edit Mode
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        instance->toggleEditing();
}


// Triangulation routines
std::pair<double, double> conics::getBisector(Vertex v1, Vertex v2){
    /*
     * Calculates the perpendicular bisector of 2 vertices
     * Returns the slope and constant value of the bisector
     */
    if(v2.x-v1.x == 0)
        Logger::log(ERROR, "Triangulation failed, parallel lines", __FILENAME__);
    double mid_x = (v2.x+v1.x)/2;
    double mid_y = (v2.y+v1.y)/2;
    double m = (v2.y-v1.y)/(v2.x-v1.x);
    double perp_m = -1/m;
    double c = mid_y - (mid_x*perp_m);
    return std::make_pair(perp_m, c);
}

std::pair<double, double> conics::getLine(double x1, double y1, double x2, double y2){
    /*
     * Return slope and constant of line given vertices
     */
    if(x2-x1 == 0)
        Logger::log(ERROR, "Triangulation failed, parallel lines", __FILENAME__);
    double m = (y2-y1)/(x2-x1);
    double c = y1 - (x1*m);
    return std::make_pair(m, c);
}

conics::Vertex conics::getIntersection(std::pair<double,double>& line1, std::pair<double,double>& line2){
    /*
     * Takes two lines
     * Returns their point of intersection
     */
    double int_X = (line2.second-line1.second)/(line1.first-line2.first);
    double int_Y = line1.first * int_X + line1.second;
    return Vertex((float) int_X, (float) int_Y);
}

std::pair<conics::Vertex,double> conics::getCenterAndRadius(conics::Triangle& t){
    /*
     * Takes a triangle
     * Returns its center point and radius as a pair
     */
    // Get circumcenter of triangle
    std::pair<double, double> bisector1 = getBisector(t.v1, t.v2);
    std::pair<double, double> bisector2 = getBisector(t.v1, t.v3);
    Vertex center = getIntersection(bisector1, bisector2);
    // Get radius
    // Distance between edges of triangle
    double e1 = sqrt(pow(t.v2.x-t.v1.x,2)+ pow(t.v2.y-t.v1.y,2));
    double e2 = sqrt(pow(t.v3.x-t.v1.x,2)+ pow(t.v3.y-t.v1.y,2));
    double e3 = sqrt(pow(t.v2.x-t.v3.x,2)+ pow(t.v2.y-t.v3.y,2));
    double radius = (e1*e2*e3)/(sqrt((e1+e2+e3)*(e2+e3-e1)*(e3+e1-e2)*(e1+e2-e3)));

    return std::make_pair(center, radius);
}

bool conics::isinCircumcircle(conics::Vertex& point, std::pair<conics::Vertex,double>&& circle){
    /*
     * Takes a point and a circle
     * Checks if the point is contained within the circle
     */
    if(pow(point.x - circle.first.x,2)+pow(point.y - circle.first.y,2) < pow(circle.second,2))
        return true;
    return false;
}

std::vector<GLfloat> conics::delaunay(std::vector<Vertex> &points) {
    /*
     * Delaunay triangulation - Bowyer-Watson algorithm
     * Takes a set of points, constructs triangle vertices
     * So that it can be rendered as a surface mesh
     */

    std::vector<Triangle> triangulation; // Contains final result
    // Encompasses all reasonable points
    Triangle super_triangle(Vertex(0.0f,50.0f), Vertex(-50.0f, -50.0f), Vertex(50.0f,-50.0f));
    triangulation.push_back(super_triangle);

    std::vector<Triangle> bad_triangles;
    std::vector<Edge> polygons;

    for(auto& point : points){ // Add points to the triangulation
        bad_triangles.clear();
        polygons.clear();

        // Find all triangles that are invalid due to the insertion
        for(auto& tri : triangulation){
            if(isinCircumcircle(point, getCenterAndRadius(tri))){
                bad_triangles.push_back(tri);
            }
        }

        // Find boundary of polygon hole
        for(auto it1 = triangulation.begin(); it1 != triangulation.end(); ++it1){
            int shared[3] = {0};
            for(auto it2 = it1+1; it2 != triangulation.end(); ++it2){
                if(it1->e1 == it2->e1)
                    shared[0] = 1;
                if(it1->e2 == it2->e2)
                    shared[1] = 1;
                if(it1->e3 == it2->e3)
                    shared[2] = 1;
            }
            if(shared[0] == 0)
                polygons.push_back(it1->e1);
            if(shared[1] == 0)
                polygons.push_back(it1->e2);
            if(shared[2] == 0)
                polygons.push_back(it1->e3);
        }

        // Remove bad triangles from triangulations
        for(auto it = triangulation.begin(); it != triangulation.end();){
            if(std::find(bad_triangles.begin(), bad_triangles.end(), *it) != bad_triangles.end())
                it = triangulation.erase(it);
            else
                ++it;
        }

        // Re-triangulate the polygonal hole
        for(auto& e : polygons){
            Triangle t(e.v1, e.v2, point);
            triangulation.push_back(t);
        }
    }

    // Insertions complete, clean-up
    auto it = triangulation.begin();
    while(it != triangulation.end()) {

        if((it->v1 == super_triangle.v1 || it->v2 == super_triangle.v1 || it->v3 == super_triangle.v1)  ||
            (it->v1 == super_triangle.v2 || it->v2 == super_triangle.v2 || it->v3 == super_triangle.v2) ||
            (it->v1 == super_triangle.v3 || it->v3 == super_triangle.v3 || it->v3 == super_triangle.v3))
        {
            it = triangulation.erase(it);
        }
        else ++it;
    }

    // Convert triangulations to float vector
    std::vector<GLfloat> result;
    for(auto& t : triangulation){
        result.push_back(t.v1.x);
        result.push_back(t.v1.y);
        result.push_back(0.0f);

        result.push_back(t.v2.x);
        result.push_back(t.v2.y);
        result.push_back(0.0f);

        result.push_back(t.v3.x);
        result.push_back(t.v3.y);
        result.push_back(0.0f);

    }

    return result;
}
