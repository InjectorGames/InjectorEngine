#version 410

layout(push_constant) uniform FragmentConstants
{
	layout(offset = 64) vec4 color;
} u_Constants;

layout(location = 0) out vec4 o_Color;

void main()
{
    o_Color = u_Constants.color;
}
