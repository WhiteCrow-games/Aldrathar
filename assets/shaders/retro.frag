#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform float tiltShiftStrength;

out vec4 finalColor;

void main()
{
    vec2 uv = fragTexCoord;
    vec2 texel = 1.0 / vec2(textureSize(texture0, 0));

    // Imagen original.
    vec4 original = texture(texture0, uv);

    // Desenfoque vertical de cinco muestras.
    // Se calcula sobre la textura interna, no sobre la ventana ampliada.
    vec4 blurred =
        texture(texture0, uv + vec2(0.0, -2.0 * texel.y)) * 0.12 +
        texture(texture0, uv + vec2(0.0, -1.0 * texel.y)) * 0.22 +
        original * 0.32 +
        texture(texture0, uv + vec2(0.0,  1.0 * texel.y)) * 0.22 +
        texture(texture0, uv + vec2(0.0,  2.0 * texel.y)) * 0.12;

    // Banda central enfocada y desenfoque progresivo en los extremos.
    float distanceFromCenter = abs(uv.y - 0.5);
    float edgeBlur = smoothstep(0.17, 0.44, distanceFromCenter);
    float blurAmount = clamp(edgeBlur * tiltShiftStrength, 0.0, 1.0);

    vec4 color = mix(original, blurred, blurAmount);

    // Tratamiento cromático retro de Aldrathar.
    float gray = dot(
        color.rgb,
        vec3(0.299, 0.587, 0.114)
    );

    color.rgb = mix(vec3(gray), color.rgb, 0.72);
    color.rgb = (color.rgb - 0.5) * 1.10 + 0.5;

    // Tinte terroso sutil.
    color.r *= 1.035;
    color.g *= 1.010;
    color.b *= 0.955;

    color.rgb = clamp(color.rgb, 0.0, 1.0);

    finalColor = color * fragColor;
}
