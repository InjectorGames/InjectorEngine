in highp vec3 f_Normal;
out highp vec4 o_Color;

uniform highp vec4 u_ObjectColor;
uniform highp vec4 u_AmbientColor;
uniform highp vec4 u_LightColor;
uniform highp vec3 u_LightDirection;

void main()
{
    vec4 ambientColor = u_ObjectColor * u_AmbientColor;

    float diffuse = max(dot(f_Normal, u_LightDirection), 0.0);
    vec4 diffuseColor =  u_LightColor * diffuse;

    o_Color = (ambientColor + diffuseColor) * u_ObjectColor;
}
