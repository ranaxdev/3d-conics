#ifndef _H_HARNESS
#define _H_HARNESS

#include <vector>
#include <memory>
#include <functional>
#include <cmath>

#include "Utils/KeyListener.h"
#include "Renderer.h"


namespace conics{

    // Window properties
    struct Window{
        uint16_t width, height;
        const char* title;
        float color[4]{};

        explicit Window(uint16_t w=640, uint16_t h=480, const char* title="empty",
                        float r=1.0f, float g=1.0f, float b =0.0f)
        : width(w), height(h), title(title){
            color[0] = r;
            color[1] = g;
            color[2] = b;
            color[3] = 1.0f;
        }
    };

    // OpenGL rendering harness
    class Harness{
        // Probably replace with dynamic container later
        int keys_to_poll[4] =
                {GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D};
        int currentKey    = 0;
        int currentAction = 0;
    public:
        Harness() = default;
        virtual ~Harness();

        void setWindow(const Window& window); // Call before running otherwise defaults
        const Window& getWindow() const;

        void setKA(const int& key, const int& action);

        void addKeyListener(const std::shared_ptr<KeyListener>& k);

        virtual void run(Harness* h);
        virtual void startup();
        virtual void render(float currentTime);

    private:
        Window w;
        std::vector<std::shared_ptr<KeyListener>> keylisteners;

    protected:
        GLuint VAO;
        GLuint buf[1024];
        Renderer* renderer;
    };

    // GLFW callbacks
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Triangulation data structures
    struct Vertex{
        /*
         * Represents a single vertex of a triangle
         */
        float x,y;
        Vertex(float x, float y):x(x), y(y)
        {}

        bool operator==(const Vertex& other) const{
            if(x == other.x && y == other.y)
                return true;
            return false;
        }
    };

    struct Edge{
        /*
         * Represents a single edge of a triangle
         * Connecting 3 vertices
         */
        Vertex v1, v2;
        Edge(Vertex& v1, Vertex& v2): v1(v1), v2(v2)
        {}


        bool operator==(const Edge& other) const{
            if(v1.x == other.v1.x && v1.y == other.v1.y && v2.x == other.v2.x && v2.y == other.v2.y)
                return true;
            return false;
        }

        size_t operator()(const Edge& edgeHash) const noexcept{
            auto hash = (size_t)(v1.x + 5 * v1.y + 6 * v2.x + 7 + v2.y);
            return hash;
        }
    };

    struct Triangle{
        /*
         * Has 3 vertices and 3 edges that connect
         * The vertices together
         */
        Vertex v1,v2,v3;
        Edge e1, e2, e3;

        Triangle(Vertex& v1, Vertex& v2, Vertex& v3)
        :v1(v1),v2(v2),v3(v3),
        e1(v1,v2), e2(v2,v3), e3(v1,v3)
        {}

        Triangle(Vertex&& v1, Vertex&& v2, Vertex&& v3)
        : Triangle(v1,v2,v3)
        {}

        bool operator==(const Triangle& other) const{
            if(v1 == other.v1 && v2 == other.v2 && v3 == other.v3)
                return true;
            return false;
        }
    };


    // Triangulation-related routines
    std::pair<double, double> getBisector(Vertex v1, Vertex v2);
    std::pair<double, double> getLine(double x1, double y1, double x2, double y2);
    Vertex getIntersection(std::pair<double,double>& line1, std::pair<double,double>& line2);
    std::pair<Vertex,double> getCenterAndRadius(Triangle& t);
    bool isinCircumcircle(Vertex& point, std::pair<Vertex,double>&& circle);

    // Bowyer-Watson (delaunay triangulation) routine
    std::vector<GLfloat> delaunay(std::vector<Vertex>& points);

}

#endif