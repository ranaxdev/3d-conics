#version 450 core

in vec4 vcolor;
out vec4 color;

void main(void){
    //color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    color = vcolor;
}