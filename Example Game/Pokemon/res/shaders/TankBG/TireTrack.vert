#version 130

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec2 texCoord0;

// Matrix which represents the position relative to the ground.
uniform mat4 modelMatrix;

void main() {
    texCoord0 = texCoord;

    vec4 pos = modelMatrix * vec4(position, 1);

    gl_Position = vec4(pos.x, -pos.z, 0, 1);
}