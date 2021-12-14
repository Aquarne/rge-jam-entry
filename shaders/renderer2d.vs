#version 430 core

layout (location = 0) in vec2 pos;

layout (location = 1) uniform mat4 model;
layout (location = 2) uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(pos, 0.0, 1.0);
}
