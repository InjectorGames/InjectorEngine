#version 420

layout(location = 0) in vec3 f_Normal;
layout(location = 1) in vec2 f_TexCoord;

layout(location = 0) out vec4 o_Color;

layout(binding = 0) uniform FragmentBufferObject
{
	vec4 objectColor;
	vec4 ambientColor;
	vec4 lightColor;
	vec3 lightDirection;
    vec2 imageScale;
    vec2 imageOffset;
} fbo;

layout(binding = 1) uniform sampler2D u_Image;

float getDiffuse(vec3 normal, vec3 direction)
{
    return max(dot(normal, direction), 0.0);
}

void main()
{
    vec4 ambientColor = fbo.objectColor * fbo.ambientColor;
    vec4 diffuseColor =  fbo.lightColor * getDiffuse(f_Normal, fbo.lightDirection);

    o_Color = (ambientColor + diffuseColor) * fbo.objectColor *
        texture(u_Image, (f_TexCoord + fbo.imageOffset) * fbo.imageScale);
}
