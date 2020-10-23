#version 410

layout(push_constant) uniform VertexPushConstant
{
	mat4 mvp;
} vpc;

layout(location = 0) in vec3 v_Position;

void main()
{
    gl_Position = vpc.mvp * vec4(v_Position, 1.0);
}
