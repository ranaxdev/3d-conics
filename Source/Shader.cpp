#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

Shader::Shader(std::string&& vshader_path, std::string&& fshader_path) {
    // Shader source code
    std::string vshader_src;
    std::string fshader_src;

    // Shader files
    std::ifstream vshader_f;
    std::ifstream fshader_f;

    // Open files, read, store GLSL
    try {
        vshader_f.open(vshader_path);
        fshader_f.open(fshader_path);

        std::stringstream vshader_stream, fshader_stream;

        vshader_stream << vshader_f.rdbuf();
        fshader_stream << fshader_f.rdbuf();

        vshader_src = vshader_stream.str();
        fshader_src = fshader_stream.str();
    } catch (std::ifstream::failure& e){
        // TODO
        // Log error msg
        std::cout << e.what() << std::endl;
    }

    // Src string -> const char*
    const char* vshader_code = vshader_src.c_str();
    const char* fshader_code = fshader_src.c_str();

    // Generate shaders: Compilation
    /* Vertex Shader */
    Shader::vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Shader::vertex_shader, 1, &vshader_code, nullptr);
    glCompileShader(Shader::vertex_shader);
    Shader::compile_error_checking(vertex_shader);

    /* Fragment Shader */
    Shader::fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Shader::fragment_shader, 1, &fshader_code, nullptr);
    glCompileShader(Shader::fragment_shader);
    Shader::compile_error_checking(fragment_shader);


    // Generate shader program : Linking
    Shader::program = glCreateProgram();
    glAttachShader(Shader::program, Shader::vertex_shader);
    glAttachShader(Shader::program, Shader::fragment_shader);
    glLinkProgram(Shader::program);
    Shader::link_error_checking(Shader::program);

    // Clear memory
    glDeleteShader(Shader::vertex_shader);
    glDeleteShader(Shader::fragment_shader);

}

Shader::~Shader() {
    glDeleteProgram(Shader::program);
}

void Shader::bind() const {
    glUseProgram(Shader::program);
}

void Shader::unbind() const {
    glUseProgram(0);
}

int Shader::get_attrib_loc(const char *var) const {
    GLint loc = glGetAttribLocation(Shader::program, var);
    return (int)loc;
}

void Shader::compile_error_checking(GLuint shader) {
    // Check for compilation errors
    int success;
    char info_log[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader, 1024, nullptr, info_log);
        // TODO
        // Replace with logger error checking msg
        std::cout << "[ERROR] Shader compilation error" << std::endl;
        std::cout << info_log << std::endl;
        std::cout << "==========================================" << std::endl;
    }
}

void Shader::link_error_checking(GLuint program) {
    // Check for linking errors
    int success;
    char info_log[1024];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(program, 1024, nullptr, info_log);
        // TODO
        // Replace with logger error checking msg
        std::cout << "[ERROR] Shader linking error" << std::endl;
        std::cout << info_log << std::endl;
        std::cout << "==========================================" << std::endl;
    }
}
