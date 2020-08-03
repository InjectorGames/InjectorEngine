#version 330

in vec3 f_Color;
out vec4 o_Color;
uniform vec4 u_Color;

void main()
{
    o_Color = vec4(f_Color, 1.0) * u_Color;
}
