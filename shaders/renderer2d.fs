#version 430 core

in vec2 f_texcoord;

out vec4 frag_color;

layout (location = 0) uniform vec4 color;

uniform sampler2D texture0;

void main()
{
    frag_color = color;
    
    vec4 texture_color = texture(texture0, f_texcoord);
    if (texture_color != vec4(0, 0, 0, 1))
    {
        frag_color *= texture_color;
    }
}
