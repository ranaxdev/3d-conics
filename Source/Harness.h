#ifndef _H_HARNESS
#define _H_HARNESS

namespace conics{

    // Window properties
    struct Window{
        uint16_t width, height;
        const char* title;

        Window(uint16_t w, uint16_t h, const char* title) : width(w), height(h), title(title){}
    };

    // OpenGL render harness
    class Harness{
    private:
        Window w;

    public:
        explicit Harness(const Window& w);
        virtual ~Harness();

        virtual void run(Harness* h);
        virtual void startup();
        virtual void render(float currentTime);

    };
}

#endif