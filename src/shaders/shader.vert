#version 330 core

layout (location = 0) in vec3 aPos;       // Quad vertex positions (static)
layout (location = 1) in vec4 instanceData; // Per-particle data: vec3(position) + float(size)

uniform mat4 projection; // Projection matrix
uniform mat4 view;       // View matrix

out vec2 texCoords;      // Texture coordinates
out vec4 particleColor;  // Per-particle color (can be added if needed)

void main() {
    vec3 particlePos = instanceData.xyz;  // Extract position
    float particleSize = instanceData.w; // Extract size

    // Scale and translate the quad vertices
    vec3 worldPos = particlePos + aPos * particleSize;

    // Transform to clip space
    gl_Position = projection * view * vec4(worldPos, 1.0);

    // Pass texture coordinates to the fragment shader
    texCoords = aPos.xy * 0.5 + 0.5; // Map quad vertex (-0.5 to 0.5) to (0.0 to 1.0)

    // Assign a default particle color (can be replaced with per-particle color input)
    particleColor = vec4(1.0, 1.0, 1.0, 1.0); // Default white
}

