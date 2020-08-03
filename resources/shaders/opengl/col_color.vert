#version 330

in vec3 v_Position;
in vec3 v_Color;
out vec3 f_Color;
uniform mat4 u_MvpMatrix;

void main()
{
    gl_Position = u_MvpMatrix * vec4(v_Position, 1.0);
    f_Color = v_Color;
}
