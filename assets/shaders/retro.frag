#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

out vec4 finalColor;

void main()
{
    vec4 color = texture(texture0, fragTexCoord);

    float scanline =
        0.96 + 0.04 * sin(fragTexCoord.y * 240.0 * 3.14159265);

    float pattern =
        mod(floor(fragTexCoord.x * 320.0) +
            floor(fragTexCoord.y * 240.0), 2.0);

    color.rgb *= scanline;
    color.rgb += (pattern - 0.5) * 0.025;
    color.rgb = (color.rgb - 0.5) * 1.05 + 0.5;
    color.rgb = clamp(color.rgb, 0.0, 1.0);

    finalColor = color * fragColor;
}
