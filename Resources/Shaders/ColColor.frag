in highp vec3 f_Color;
out highp vec4 o_Color;
uniform highp vec4 u_Color;

void main()
{
    o_Color = vec4(f_Color, 1.0) * u_Color;
}
