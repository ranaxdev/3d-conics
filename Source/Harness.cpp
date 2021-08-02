#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/Globals.h"
#include "Utils/Logger.h"
#include "Harness.h"

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
    GLFWwindow* window = glfwCreateWindow(w.width, w.height, w.title, nullptr, nullptr);
    if(window == nullptr){
        Logger::log(ERROR, "Could not create GLFW window", __FILENAME__);
        glfwTerminate();
    }
    // Window settings
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, (void*)(this)); // Pointer to app window that implements this harness
    // GLFW settings
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Callbacks
    glfwSetKeyCallback(window, conics::key_callback);

    // Load GLAD
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Logger::log(ERROR, "Could not load GLAD", __FILENAME__);
        glfwTerminate();
    }

    // Application Initialization
    startup();

    // Application Rendering
    const GLfloat screen_color[4] = {w.color[0], w.color[1], w.color[2], w.color[3]};
    while(!glfwWindowShouldClose(window)){
        glClearBufferfv(GL_COLOR, 0, screen_color);

        // Update observers
        for(auto& o : conics::Harness::keylisteners){
            // NOTE: for key callback (NOT poll) => o->keys[currentKey] = currentAction

            // Poll tracked keys for presses & mouse positions
            for(auto& k : keys_to_poll){
                if(glfwGetKey(window, k) == GLFW_PRESS)
                    o->keys[k] = 1;
                else
                    o->keys[k] = 0;

                glfwGetCursorPos(window, &o->xpos, &o->ypos);
            }


        }

        // Render
        render((float) glfwGetTime());

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
    Harness:currentAction = action;
}



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

conics::Vertex conics::getIntersection(std::pair<double,double> line1, std::pair<double,double> line2){
    /*
     * Takes two lines
     * Returns their point of intersection
     */
    double int_X = (line2.second-line1.second)/(line1.first-line2.first);
    double int_Y = line1.first * int_X + line1.second;
    return Vertex((float) int_X, (float) int_Y);
}

std::pair<conics::Vertex,double> conics::getCenterAndRadius(conics::Triangle t){
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

bool conics::isinCircumcircle(conics::Vertex point, std::pair<conics::Vertex,double> circle){
    /*
     * Takes a point and a circle
     * Checks if the point is contained within the circle
     */
    if(pow(point.x - circle.first.x,2)+pow(point.y - circle.first.y,2) < pow(circle.second,2))
        return true;
    return false;
}