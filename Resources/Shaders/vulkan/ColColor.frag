#version 410

layout(push_constant) uniform FragmentPushConstant
{
	layout(offset = 64) vec4 color;
} fpc;

layout(location = 0) in vec3 f_Color;
layout(location = 0) out vec4 o_Color;

void main()
{
    o_Color = vec4(f_Color, 1.0) * fpc.color;
}
