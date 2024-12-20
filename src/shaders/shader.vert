#version 330 core

layout (location = 0) in vec3 aPos;       // Quad vertex positions (static)
layout (location = 1) in vec3 instanceData; // Per-particle data: vec3(position)

uniform mat4 projection; // Projection matrix
uniform mat4 view;       // View matrix

out vec2 texCoords;      // Texture coordinates
out vec4 particleColor;  // Per-particle color (can be added if needed)

uniform vec3 cameraUp;
uniform vec3 cameraRight;

void main() {
    vec3 billboardPos = instanceData + cameraRight * aPos.x + cameraUp * aPos.y;

    // transform to clip space
    gl_Position = projection * view * vec4(billboardPos, 1.0);

    texCoords = aPos.xy + vec2(0.5); // Map quad vertex (-0.5 to 0.5) to (0.0 to 1.0)
    particleColor = vec4(1, 1, 1, 1.0); // Default white
}

