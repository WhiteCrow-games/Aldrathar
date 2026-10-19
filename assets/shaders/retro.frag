#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

out vec4 finalColor;

void main()
{
    vec4 color = texture(texture0, fragTexCoord);

    // Convertir los colores a una paleta menos saturada.
    float gray = dot(
        color.rgb,
        vec3(0.299, 0.587, 0.114)
    );

    color.rgb = mix(
        vec3(gray),
        color.rgb,
        0.72
    );

    // Contraste moderado para un ambiente sombrío.
    color.rgb = (color.rgb - 0.5) * 1.10 + 0.5;

    // Tinte terroso muy sutil.
    color.r *= 1.035;
    color.g *= 1.010;
    color.b *= 0.955;

    color.rgb = clamp(color.rgb, 0.0, 1.0);

    finalColor = color * fragColor;
}
