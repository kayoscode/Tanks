#version 130
in vec2 position;

out vec2 texCoord0;

void main() {
    gl_Position = vec4(position.x, position.y, 0, 1);

    texCoord0 = position * .5 + .5;
	texCoord0.y = texCoord0.y;
}