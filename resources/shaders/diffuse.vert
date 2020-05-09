#version 330

in vec3 v_Position;
in vec3 v_Normal;

out vec3 f_Normal;

uniform mat4 u_MvpMatrix;
uniform mat3 u_NormalMatrix;

void main()
{
    gl_Position = u_MvpMatrix * vec4(v_Position, 1.0);
    f_Normal = normalize(u_NormalMatrix * v_Normal);
}
