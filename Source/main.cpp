#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>


#include "Harness.h"
#include "Shader.h"
#include "Camera.h"

#include "Utils/Math.h"
#include "Utils/Logger.h"
#include "Utils/Globals.h"






class App : public conics::Harness{
private:








public:
    std::shared_ptr<Camera> camera;
    Shader* shader;
    Shader* shader2;

    // Colors
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 green = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    glm::vec4 purple = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 orange = glm::vec4(1.0f, 0.35f, 0.0f, 1.0f);
    glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    glm::vec4 dark_green = glm::vec4(0.3f, 0.7f, 0.0f, 1.0f);

    glm::vec4 colors[61];
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


                0.5000f, 0.5000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.5000f, 0.5000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -0.5000f, 0.2300f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.2300f, 0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                -1.0000f, -0.7500f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,
                0.7300f, -0.4000f, 0.0f,
                0.6900f, 0.6900f, 0.0f,
                1.0000f, -0.8800f, 0.0f,

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
        using namespace conics;
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
        Triangle supertri(Vertex(0.0f,50.0f), Vertex(-50.0f, -50.0f), Vertex(50.0f,-50.0f));
        std::vector<Triangle> triangulation= {
                supertri
        };

        std::vector<Triangle> badTris;
        std::vector<Edge> polygon;


        for(auto& point : points){

            badTris.clear();
            polygon.clear();

            for(auto& tri : triangulation){
                if(isinCircumcircle(point, getCenterAndRadius(tri))){
                    badTris.push_back(tri);
                }
            }

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
                    polygon.push_back(it1->e1);
                if(shared[1] == 0)
                    polygon.push_back(it1->e2);
                if(shared[2] == 0)
                    polygon.push_back(it1->e3);
            }

            for(auto it = triangulation.begin(); it != triangulation.end();){
                if(std::find(badTris.begin(), badTris.end(), *it) != badTris.end()){
                    it = triangulation.erase(it);
                }
                else
                    ++it;
            }

            for(auto& e : polygon){
                Triangle t(e.v1, e.v2, point);
                triangulation.push_back(t);
            }
        }

        auto it = triangulation.begin();

        while(it != triangulation.end()) {

            if((it->v1 == supertri.v1 || it->v2 == supertri.v1 || it->v3 == supertri.v1) ||
            (it->v1 == supertri.v2 || it->v2 == supertri.v2 || it->v3 == supertri.v2) ||
            (it->v1 == supertri.v3 || it->v3 == supertri.v3 || it->v3 == supertri.v3)
            )
            {

                it = triangulation.erase(it);
            }
            else ++it;
        }


        for(auto& t : triangulation){
            printf("%4.4ff, %4.4ff, 0.0f,\n", t.v1.x, t.v1.y);
            printf("%4.4ff, %4.4ff, 0.0f,\n", t.v2.x, t.v2.y);
            printf("%4.4ff, %4.4ff, 0.0f,\n", t.v3.x, t.v3.y);

        }

        // Random colors TEMP
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0,1);
        for(int i=0; i<61; i++){
            auto r = (float) dis(gen);
            auto g = (float) dis(gen);
            auto b = (float) dis(gen);
            colors[i] = glm::vec4(r,g,b,0.5f);
        }



    };

    float delta = 0.0f;
    float last = 0.0f;

    void render(float currentTime) override {
        delta = currentTime - last;


        glPointSize(20.0f);
        glLineWidth(1.0f);


        shader2->bind();
        shader2->setMat4(20, camera->calc_VP(delta));


        int j=0;
        for(int i=0; i < (int)size/3-7; i+=3){

            shader2->setVec4(30, colors[j]);
            glDrawArrays(GL_TRIANGLES, i, 3);

            j++;
        }


        shader2->setVec4(30, red);
        glDrawArrays(GL_POINTS, 0, 7);


        shader2->setVec4(30, blue);
        glDrawArrays(GL_LINES, 7, (int)(size)/2);


        glLineWidth(20.0f);
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