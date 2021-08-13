#version 450 core
layout (location = 3) in vec3 position;
layout (location = 20) uniform mat4 vp;
layout (location = 21) uniform mat4 model;
layout (location = 30) uniform vec3 ucolor;
layout (location = 31) uniform int use_plain;

out vec4 vcolor;

void main(void){
    gl_Position = vp* model * vec4(position, 1.0f);

    if(use_plain == 0){
        vcolor = vec4(position, 1.0f);
    }
    else{
        vcolor = vec4(ucolor, 1.0f);
    }
}