out highp vec4 o_Color;

layout(std140) uniform FragmentBufferObject
{
    highp float hight;
} fbo;

void main()
{
    o_Color = vec4(1.0);
}
