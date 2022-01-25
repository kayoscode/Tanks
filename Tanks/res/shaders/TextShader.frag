#version 130

in vec2 texCoord0;

out vec4 color;

uniform vec4 textColor;
uniform sampler2D textureAtlas;

const float width = .5;
const float edge = .1;

void main(void){
	float distance = 1 - texture(textureAtlas, texCoord0).a;
	float alpha = 1 - smoothstep(width, width + edge, distance);

	color = vec4(textColor.rgb, alpha);
}