#version 300 es

in highp vec3 v_Position;
uniform highp mat4 u_MvpMatrix;

void main()
{
    gl_Position = u_MvpMatrix * vec4(v_Position, 1.0);
}
