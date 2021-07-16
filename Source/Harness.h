#ifndef _H_HARNESS
#define _H_HARNESS

#include <vector>

#include "Utils/KeyListener.h"


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
    private:
        Window w;
        std::vector<const KeyListener*> keylisteners;
    public:
        Harness() = default;
        virtual ~Harness() = default;

        void setWindow(const Window& window); // Call before running otherwise defaults
        const Window& getWindow() const;

        void addKeyListener(const KeyListener* k);

        virtual void run(Harness* h);
        virtual void startup();
        virtual void render(float currentTime);

    };
}

#endif