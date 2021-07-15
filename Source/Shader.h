#ifndef _H_SHADER
#define _H_SHADER

#include <GLFW/glfw3.h>

class Shader{
public:
    Shader() = default;
    Shader(const char* vshader_path, const char* fshader_path);
    ~Shader();

    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;

    void bind() const;
    void unbind() const;
    int get_attrib_loc(const char* var) const;

private:
    void compile_error_checking(GLuint shader);
    void link_error_checking(GLuint program);
};


#endif