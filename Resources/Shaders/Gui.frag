in highp vec2 f_TexCoord;
in highp vec4 f_Color;

out highp vec4 o_Color;

uniform highp vec2 u_ImageScale;
uniform highp vec2 u_ImageOffset;
uniform highp sampler2D u_Image;

void main()
{
    o_Color = f_Color * texture(u_Image,
        (f_TexCoord.st + u_ImageOffset) * u_ImageScale);
}
