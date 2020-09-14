in highp vec3 f_Normal;
out highp vec4 o_Color;

layout(std140) uniform FragmentBufferObject
{
    highp vec4 objectColor;
    highp vec4 ambientColor;
    highp vec4 lightColor;
    highp vec3 lightDirection;
} fbo;

void main()
{
    vec4 ambientColor = fbo.objectColor * fbo.ambientColor;

    float diffuse = max(dot(f_Normal, fbo.lightDirection.xyz), 0.0);
    vec4 diffuseColor = fbo.lightColor * diffuse;

    o_Color = (ambientColor + diffuseColor) * fbo.objectColor;
}
