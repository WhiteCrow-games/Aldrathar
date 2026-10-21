#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform sampler2D texture0;

void main()
{
    vec4 color = texture2D(texture0, fragTexCoord);

    float gray = dot(
        color.rgb,
        vec3(0.299, 0.587, 0.114)
    );

    color.rgb = mix(vec3(gray), color.rgb, 0.72);
    color.rgb = (color.rgb - 0.5) * 1.10 + 0.5;

    color.r *= 1.035;
    color.g *= 1.010;
    color.b *= 0.955;

    color.rgb = clamp(color.rgb, 0.0, 1.0);

    gl_FragColor = color * fragColor;
}
