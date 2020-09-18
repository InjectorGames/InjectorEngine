layout (location = 0) in highp vec3 v_Position;
layout (location = 1) in highp vec3 v_Normal;
layout (location = 2) in highp vec2 v_TexCoord;

out highp vec3 f_Normal;
out highp vec2 f_TexCoord;

uniform highp mat4 u_MVP;
uniform highp mat3 u_Normal;

void main()
{
    gl_Position = u_MVP * vec4(v_Position, 1.0);
    f_Normal = normalize(u_Normal * v_Normal);
    f_TexCoord = vec2(v_TexCoord.x, -v_TexCoord.y);
}
