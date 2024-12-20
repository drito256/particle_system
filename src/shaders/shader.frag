#version 330 core

in vec2 texCoords;        // Interpolated texture coordinates
in vec4 particleColor;    // Particle color (from vertex shader)

uniform sampler2D particleTexture; // Texture sampler

out vec4 FragColor;

void main() {
    // Sample the particle's texture
    vec4 texColor = texture(particleTexture, texCoords);

    // Multiply texture color with particle color
    FragColor = texColor * particleColor;

    if (FragColor.a < 0.05)
        discard;
}

