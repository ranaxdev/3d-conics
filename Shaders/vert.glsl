#version 450 core
layout (location = 0) in vec3 position;
layout (location = 20) uniform mat4 vp;

void main(void){
    gl_Position = vp* vec4(position, 1.0f);
}