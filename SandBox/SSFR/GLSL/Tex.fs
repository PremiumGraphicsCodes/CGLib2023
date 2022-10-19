#version 150
uniform sampler2D texture;
in vec2 texCoord;
out vec4 fragColor;
void main(void) {
	fragColor = texture2D(texture, texCoord);
//	fragColor.r = 1.0;
}
