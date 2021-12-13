#version 430 core

out vec4 frag_color;

layout (location = 0) uniform vec4 color;

void main()
{
    frag_color = color;
}
