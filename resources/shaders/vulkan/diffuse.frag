#version 420

layout(location = 0) in vec3 f_Normal;
layout(location = 0) out vec4 o_Color;

layout(binding = 0) uniform FragmentBufferObject
{
	layout(offset = 0) vec4 objectColor;
	layout(offset = 16) vec4 ambientColor;
	layout(offset = 32) vec4 lightColor;
	layout(offset = 48) vec3 lightDirection;
} fbo;

void main()
{
    vec4 ambientColor = fbo.objectColor * fbo.ambientColor;

    float diffuse = max(dot(f_Normal, fbo.lightDirection), 0.0);
    vec4 diffuseColor =  fbo.lightColor * diffuse;

    o_Color = (ambientColor + diffuseColor) * fbo.objectColor;
}
