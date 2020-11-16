(location = 0) in highp vec2 v_Position;
(location = 1) in highp vec2 v_TexCoord;
(location = 2) in highp vec4 v_Color;

out highp vec2 f_TexCoord;
out highp vec4 f_Color;
 
uniform highp mat4 u_Proj;
 
void main()
{
    f_TexCoord = v_TexCoord;
    f_Color = v_Color;
    gl_Position = u_Proj * vec4(v_Position.xy, 0.0, 1.0);
}
