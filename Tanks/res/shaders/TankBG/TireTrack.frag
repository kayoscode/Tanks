#version 130
out vec4 color;

in vec2 texCoord0;

uniform sampler2D tankTracksTexture;

void main() {
	color = texture(tankTracksTexture, texCoord0);
}