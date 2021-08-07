#version 450 core
layout (location = 3) in vec3 position;
layout (location = 20) uniform mat4 vp;
layout (location = 30) uniform vec4 ucolor;

out vec4 vcolor;

void main(void){
    gl_Position = vp* vec4(position, 1.0f);
    vcolor = vec4(abs(position), 1.0f);
}