#version 410

layout(push_constant) uniform VertexPushConstant
{
    layout(offset = 0) mat4 mvp;
} vpc;

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Color;

layout(location = 0) out vec3 f_Color;

void main()
{
    gl_Position = vpc.mvp * vec4(v_Position, 1.0);
    f_Color = v_Color;
}
