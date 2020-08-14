#version 410

layout(push_constant) uniform VertexConstants
{
	layout(offset = 0) mat4 mvp;
} u_Constants;

layout(location = 0) in vec3 v_Position;

void main()
{
    gl_Position = u_Constants.mvp * vec4(v_Position, 1.0);
}
