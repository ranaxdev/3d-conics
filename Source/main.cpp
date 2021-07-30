#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>


#include "Harness.h"
#include "Shader.h"
#include "Camera.h"

#include "Utils/Math.h"
#include "Utils/Logger.h"
#include "Utils/Globals.h"

struct Vertex{
    float x,y;
    Vertex(float x, float y):x(x), y(y)
    {}
};
struct Triangle{
    Vertex v1,v2,v3;
    Triangle(Vertex v1, Vertex v2, Vertex v3):v1(v1),v2(v2),v3(v3)
    {}
};

class App : public conics::Harness{
private:
    std::pair<double, double> getBisector(Vertex v1, Vertex v2){
        if(v2.x-v1.x == 0)
            Logger::log(ERROR, "Triangulation failed, parallel lines", __FILENAME__);
        double mid_x = (v2.x+v1.x)/2;
        double mid_y = (v2.y+v1.y)/2;
        double m = (v2.y-v1.y)/(v2.x-v1.x);
        double perp_m = -1/m;
        double c = mid_y - (mid_x*perp_m);
        return std::make_pair(perp_m, c);
    }
    std::pair<double, double> getLine(double x1, double y1, double x2, double y2){
        if(x2-x1 == 0)
            Logger::log(ERROR, "Triangulation failed, parallel lines", __FILENAME__);
        double m = (y2-y1)/(x2-x1);
        double c = y1 - (x1*m);
        return std::make_pair(m, c);
    }
    Vertex getIntersection(std::pair<double,double> line1, std::pair<double,double> line2){
        double int_X = (line2.second-line1.second)/(line1.first-line2.first);
        double int_Y = line1.first * int_X + line1.second;
        return Vertex((float) int_X, (float) int_Y);
    }
    std::pair<Vertex,double> getCenterAndRadius(Triangle t){
        // Get circumcenter of triangle
        std::pair<double, double> bisector1 = getBisector(t.v1, t.v2);
        std::pair<double, double> bisector2 = getBisector(t.v1, t.v3);
        Vertex center = getIntersection(bisector1, bisector2);
        // Get radius
        
    }
    bool isinCircumcircle(Vertex point){

    }


public:
    std::shared_ptr<Camera> camera;
    Shader* shader;
    Shader* shader2;

    // Colors
    glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 green = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);


    // Indexed drawing stuff
    int size =0;

    void startup() override {
        shader = new Shader(SRC+"Shaders/vert.glsl", SRC+"Shaders/frag.glsl");
        shader2 = new Shader(SRC+"Shaders/overt.glsl", SRC+"Shaders/ofrag.glsl");

        shader->bind();

        GLfloat data[] = {
                // Axis 1 (red)
                0.0f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, -5.0f,    1.0f, 0.0f, 0.0f,

                // Axis 2 (green)
                0.0f, 2.5f, -2.5f,    0.0f, 1.0f, 0.0f,
                0.0f, -2.5f, -2.5f,   0.0f, 1.0f, 0.0f,

                // Axis 3 (blue)
                2.5f, 0.0f, -2.5f,    0.0f, 0.0f, 1.0f,
                -2.5f, 0.0f, -2.5f,   0.0f, 0.0f, 1.0f
        };

        std::vector<float> data2 = {
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.23f, 0.0f,
                0.23f, 0.75f, 0.0f,
                -1.0f, -0.75f, 0.0f,
                0.73f, -0.40f, 0.0f,
                0.69f, 0.69f, 0.0f,
                1.0f, -0.88f, 0.0f,

                0.0f, 50.0f, 0.0f,
                -50.0f, -50.0f, 0.0f,
                50.0f, -50.0f, 0.0f
        };
        size = (int) data2.size();
        int dat_size = 4*size;

        GLuint VAO;
        GLuint buffer[3];
        glCreateVertexArrays(1, &VAO);
        glCreateBuffers(3, buffer);

        /* Axis data */
        glNamedBufferStorage(buffer[0], sizeof(data), data, GL_MAP_READ_BIT|GL_MAP_WRITE_BIT);

        // Position
        glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(VAO, 0, 0);
        glEnableVertexArrayAttrib(VAO, 0);
        // Color
        glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float));
        glVertexArrayAttribBinding(VAO, 1, 0);
        glEnableVertexArrayAttrib(VAO, 1);

        glVertexArrayVertexBuffer(VAO, 0, buffer[0], 0, 6*sizeof(float));

        /* Other data */
        glNamedBufferStorage(buffer[1], dat_size, nullptr, GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
        float* ptr = (float*) glMapNamedBufferRange(buffer[1], 0, dat_size, GL_MAP_WRITE_BIT|GL_MAP_READ_BIT);
        for(int i=0; i<size; i++){
            ptr[i] = data2[i];
        }
        glUnmapNamedBuffer(buffer[1]);

        glVertexArrayAttribFormat(VAO, 3, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(VAO, 3, 1);
        glEnableVertexArrayAttrib(VAO, 3);

        glVertexArrayVertexBuffer(VAO, 1, buffer[1], 0, 3*sizeof(float));


        glBindVertexArray(VAO);

        // Bowyer attempt #1
        std::vector<Vertex> points = {
                Vertex(0.5f, 0.5f),
                Vertex(-0.5f, 0.23f),
                Vertex(0.23f, 0.75f),
                Vertex(-1.0f, -0.75f),
                Vertex(0.73f, -0.40f),
                Vertex(0.69f, 0.69f),
                Vertex(1.0f, -0.88f),

                Vertex(0.0f, 50.0f),
                Vertex(-50.0f, -50.0f),
                Vertex(50.0f, -50.0f),
        };
        std::vector<Triangle> triangulation= {
                Triangle(Vertex(0.0f,50.0f), Vertex(-50.0f, -50.0f), Vertex(50.0f,-50.0f))
        };

        std::vector<std::vector<Vertex>> badTris;

        for(auto& p : points){
            badTris = {};
            for(auto& t : triangulation){

            }
        }



    };

    float delta = 0.0f;
    float last = 0.0f;
    void render(float currentTime) override {
        delta = currentTime - last;


        glPointSize(20.0f);
        glLineWidth(40.0f);


        shader2->bind();
        shader2->setMat4(20, camera->calc_VP(delta));
        shader2->setVec4(30, cyan);
        glDrawArrays(GL_POINTS, 0, (int)size/3);


        shader->bind();
        shader->setMat4(20, camera->calc_VP(delta));
        glDrawArrays(GL_LINES , 0, 8);


        last = currentTime;
    }
};


#define DEBUG 0
#if !DEBUG
int main(){
    conics::Window window = conics::Window(1280, 960, "conics");
    std::shared_ptr<Camera> camera(new Camera);
    App* a = new App;
    a->setWindow(window);
    a->addKeyListener(camera);
    a->camera = camera;

    a->run(a);
    delete a;
    
    return 0;
}


#else

int main(){
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float angle = 0.0f;
    std::vector<float> v;
    std::vector<float> dat;
    dat.push_back(55);
    dat.push_back(27);
    dat.push_back(69);
    std::cout << dat[0] << " " << dat[1] << " " << dat[2] << std::endl;
    for(int i=0; i < 5; i++){
        z = (float)i;
        for(int a=0; a<360; a++){
            x = (float) (sqrt(z) * cos(glm::radians((float)a)));
            y = (float) (sqrt(z) * sin(glm::radians((float)a)));
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            //printf("%4.4ff, %4.4ff, %4.4ff,\n",x,y,z);


        }
    }

    return 0;
}

#endif