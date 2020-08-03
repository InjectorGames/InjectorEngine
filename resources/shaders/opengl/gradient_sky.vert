#version 330

in vec3 v_Position;
out vec4 v_Color;

uniform float u_Pitch;
uniform vec3 u_UpColor;
uniform vec3 u_DownColor;

void main()
{
    gl_Position = vec4(v_Position, 1.0);

    // (1.0 / 1.570796326)
    const float norm = 0.636619; 

    if(v_Position.y < 0.0)
    {
        v_Color = vec4(mix(u_UpColor, u_DownColor, (u_Pitch * norm + 1.5) / 2.0), 1.0);
    }
    else
    {
        v_Color = vec4(mix(u_UpColor, u_DownColor, (u_Pitch * norm + 0.5) / 2.0), 1.0);
    }
}
