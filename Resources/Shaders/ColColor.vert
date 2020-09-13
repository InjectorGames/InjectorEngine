layout (location = 0) in highp vec3 v_Position;
layout (location = 1) in highp vec4 v_Color;

out highp vec4 f_Color;

uniform highp mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(v_Position, 1.0);
    f_Color = v_Color;
}
