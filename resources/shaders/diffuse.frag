#version 330

in vec3 f_Normal;
out vec4 o_Color;

uniform vec3 u_ObjectColor;
uniform vec3 u_AmbientColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightDirection;

void main()
{
    vec3 ambientColor = u_ObjectColor * u_AmbientColor;

    float diffuse = max(dot(f_Normal, u_LightDirection), 0.0);
    vec3 diffuseColor = diffuse * u_LightColor;

    vec3 color = (ambientColor + diffuseColor) * u_ObjectColor;
    o_Color = vec4(color, 1.0);
}
