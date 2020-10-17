in highp vec3 f_Normal;
in highp vec2 f_TexCoord;

out highp vec4 o_Color;

layout(std140) uniform FragmentBufferObject
{
    highp vec4 objectColor;
    highp vec4 ambientColor;
    highp vec4 lightColor;
    highp vec4 lightDirection;
    highp vec2 imageScale;
    highp vec2 imageOffset;
} fbo;

uniform sampler2D u_Image;

float getDiffuse(vec3 normal, vec3 direction)
{
    return max(dot(normal, direction), 0.0);
}

void main()
{
    vec4 ambientColor = fbo.objectColor * fbo.ambientColor;
    vec4 diffuseColor = fbo.lightColor * getDiffuse(f_Normal, fbo.lightDirection.xyz);

    o_Color = (ambientColor + diffuseColor) * fbo.objectColor *
        image(u_Image, (f_TexCoord + fbo.imageOffset) * fbo.imageScale);
}
