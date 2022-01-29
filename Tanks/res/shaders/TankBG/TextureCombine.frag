#version 130
out vec4 color;

in vec2 texCoord0;

uniform sampler2D backgroundTexture;
uniform sampler2D tankTracksTexture;

void main() {
    vec4 bg = texture(backgroundTexture, texCoord0);
	vec4 tracks = texture(tankTracksTexture, texCoord0);
	
	if(tracks.r < .3 && tracks.g < .3 && tracks.b < .3)
	{
		color = tracks;
	}
	else
	{
		color = bg;
	}
}