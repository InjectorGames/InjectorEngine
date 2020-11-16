in highp f_TexCoord;
in highp f_Color;

out highp vec4 o_Color;

uniform highp sampler2D u_Image;

void main()
{
    o_Color = f_Color * texture(u_Image, f_TexCoord.st);
}
