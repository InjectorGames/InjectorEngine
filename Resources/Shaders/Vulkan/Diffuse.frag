#version 420

layout(location = 0) in vec3 f_Normal;
layout(location = 0) out vec4 o_Color;

layout(binding = 0) uniform FragmentBufferObject
{
	vec4 objectColor;
	vec4 ambientColor;
	vec4 lightColor;
	vec3 lightDirection;
} fbo;

float getDiffuse(vec3 normal, vec3 direction)
{
    return max(dot(normal, direction), 0.0);
}

void main()
{
    vec4 ambientColor = fbo.objectColor * fbo.ambientColor;
    vec4 diffuseColor =  fbo.lightColor * getDiffuse(f_Normal, fbo.lightDirection);

    o_Color = (ambientColor + diffuseColor) * fbo.objectColor;
}
