#ifndef _H_HARNESS
#define _H_HARNESS

namespace conics{

    // Window properties
    struct Window{
        uint16_t width, height;
        const char* title;

        explicit Window(uint16_t w=640, uint16_t h=480, const char* title="empty") : width(w), height(h), title(title){}
    };

    // OpenGL render harness
    class Harness{
    private:
        Window w;

    public:
        explicit Harness(const Window& w);
        Harness() = default;
        virtual ~Harness() = default;

        virtual void run(Harness* h);
        virtual void startup();
        virtual void render(float currentTime);

    };
}

#endif