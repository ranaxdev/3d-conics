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
        // Distance between edges of triangle
        double e1 = sqrt(pow(t.v2.x-t.v1.x,2)+ pow(t.v2.y-t.v1.y,2));
        double e2 = sqrt(pow(t.v3.x-t.v1.x,2)+ pow(t.v3.y-t.v1.y,2));
        double e3 = sqrt(pow(t.v2.x-t.v3.x,2)+ pow(t.v2.y-t.v3.y,2));
        double radius = (e1*e2*e3)/(sqrt((e1+e2+e3)*(e2+e3-e1)*(e3+e1-e2)*(e1+e2-e3)));

        return std::make_pair(center, radius);
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
                0.0280536f, 0.261098f, 0.0f,

                0.5570f, 0.2611f, 0.0f,
                0.1781f, -0.2461f, 0.0f,
                -0.4158f, -0.0267f, 0.0f,
                -0.3738f, 0.6051f, 0.0f,
                0.2439f, 0.7440f, 0.0f,
                0.5524f, 0.1911f, 0.0f,
                0.1096f, -0.2615f, 0.0f,
                -0.4500f, 0.0346f, 0.0f,
                -0.3247f, 0.6552f, 0.0f,
                0.3059f, 0.7112f, 0.0f,
                0.5385f, 0.1223f, 0.0f,
                0.0398f, -0.2677f, 0.0f,
                -0.4757f, 0.0999f, 0.0f,
                -0.2695f, 0.6985f, 0.0f,
                0.3631f, 0.6705f, 0.0f,
                0.5156f, 0.0560f, 0.0f,
                -0.0303f, -0.2646f, 0.0f,
                -0.4927f, 0.1680f, 0.0f,
                -0.2090f, 0.7340f, 0.0f,
                0.4143f, 0.6225f, 0.0f,
                0.4842f, -0.0068f, 0.0f,
                -0.0994f, -0.2523f, 0.0f,
                -0.5004f, 0.2377f, 0.0f,
                -0.1443f, 0.7612f, 0.0f,
                0.4587f, 0.5682f, 0.0f,
                0.4447f, -0.0648f, 0.0f,
                -0.1662f, -0.2309f, 0.0f,
                -0.4988f, 0.3078f, 0.0f,
                -0.0766f, 0.7796f, 0.0f,
                0.4956f, 0.5085f, 0.0f,
                0.3979f, -0.1170f, 0.0f,
                -0.2296f, -0.2009f, 0.0f,
                -0.4880f, 0.3772f, 0.0f,
                -0.0070f, 0.7889f, 0.0f,
                0.5242f, 0.4445f, 0.0f,
                0.3446f, -0.1627f, 0.0f,
                -0.2885f, -0.1627f, 0.0f,
                -0.4681f, 0.4444f, 0.0f,
                0.0631f, 0.7889f, 0.0f,
                0.5441f, 0.3772f, 0.0f,
                0.2858f, -0.2008f, 0.0f,
                -0.3418f, -0.1171f, 0.0f,
                -0.4395f, 0.5085f, 0.0f,
                0.1327f, 0.7796f, 0.0f,
                0.5550f, 0.3079f, 0.0f,
                0.2224f, -0.2309f, 0.0f,
                -0.3886f, -0.0648f, 0.0f,
                -0.4026f, 0.5682f, 0.0f,
                0.2004f, 0.7612f, 0.0f,
                0.5565f, 0.2377f, 0.0f,
                0.1555f, -0.2523f, 0.0f,
                -0.4281f, -0.0068f, 0.0f,
                -0.3582f, 0.6225f, 0.0f,
                0.2651f, 0.7340f, 0.0f,
                0.5488f, 0.1680f, 0.0f,
                0.0865f, -0.2646f, 0.0f,
                -0.4595f, 0.0560f, 0.0f,
                -0.3070f, 0.6705f, 0.0f,
                0.3256f, 0.6985f, 0.0f,
                0.5319f, 0.0999f, 0.0f,
                0.0164f, -0.2677f, 0.0f,
                -0.4824f, 0.1223f, 0.0f,
                -0.2498f, 0.7112f, 0.0f,
                0.3808f, 0.6552f, 0.0f,
                0.5061f, 0.0346f, 0.0f,
                -0.0535f, -0.2615f, 0.0f,
                -0.4963f, 0.1911f, 0.0f,
                -0.1878f, 0.7440f, 0.0f,
                0.4299f, 0.6051f, 0.0f,
                0.4719f, -0.0267f, 0.0f,
                -0.1220f, -0.2461f, 0.0f,
                -0.5009f, 0.2611f, 0.0f,
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

        /*
        for(auto& p : points){
            badTris = {};
            for(auto& t : triangulation){

            }
        }
        */
        Vertex v1(0.5f, 0.5f);
        Vertex v2(-0.5f, 0.23f);
        Vertex v3(0.23f, 0.75f);
        Triangle t(v1,v2,v3);
        auto i = getCenterAndRadius(t);
        std::cout << i.first.x << " " << i.first.y << std::endl;
        std::cout << i.second << std::endl;



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
        glDrawArrays(GL_TRIANGLES, 0, 3);
        shader2->setVec4(30, red);
        glDrawArrays(GL_POINTS, 3, 1);
        shader2->setVec4(30, green);
        glDrawArrays(GL_POINTS, 4, 72);

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
    double centerX = 0.0280536;
    double centerY = 0.261098;
    double radius = 0.528968;
    for(int i=0; i < 360; i+=5){
        double x = radius * cos(i) + centerX;
        double y = radius * sin(i) + centerY;
        printf("%4.4ff, %4.4ff, 0.0f,\n", x,y);

    }

    return 0;
}

#endif