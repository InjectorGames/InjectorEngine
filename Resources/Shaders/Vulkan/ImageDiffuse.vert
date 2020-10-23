#version 420

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoord;

layout(location = 0) out vec3 f_Normal;
layout(location = 1) out vec2 f_TexCoord;

layout(push_constant) uniform VertexPushConstant
{
	mat4 mvp;
	mat4 normal;
} vpc;

void main()
{
    gl_Position = vpc.mvp * vec4(v_Position, 1.0);
    f_Normal = normalize(mat3(vpc.normal) * v_Normal);
    f_TexCoord = vec2(v_TexCoord.x, -v_TexCoord.y);
}
