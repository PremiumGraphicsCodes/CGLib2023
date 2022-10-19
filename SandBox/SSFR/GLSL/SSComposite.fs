#version 150
uniform sampler2D depthTexture;
uniform sampler2D surfaceTexture;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D absorptionTexture;
uniform sampler2D backgroundTexture;
in vec2 texCoord;
out vec4 fragColor;
void main(void) {
	vec4 depth = texture2D(depthTexture, texCoord);
	vec4 surfaceColor = texture2D(surfaceTexture, texCoord);
//	fragColor = surfaceColor;
	vec4 reflectionColor = texture2D(reflectionTexture, texCoord);
	vec4 refractionColor = texture2D(refractionTexture, texCoord);
	if(depth.r < 0.01) {
		vec4 bgColor = texture2D(backgroundTexture, texCoord);
		fragColor = bgColor;
		return;
	}
	vec4 absorptionColor = texture2D(absorptionTexture, texCoord);
	surfaceColor = surfaceColor + reflectionColor * 0.5 + refractionColor * 0.5;
	fragColor = mix( absorptionColor, surfaceColor, 1.0-absorptionColor.a);
//	fragColor = surfaceColor + reflectionColor * 0.5 + refractionColor * 0.5;
//	vec4 bgColor = texture2D(backgroundTexture, texCoord);
//	if(absorptionColor.a < 0.01) {
//		fragColor = bgColor;
//		return;
//	} else { 
//		fragColor = mix( absorptionColor, surfaceColor, 1.0-absorptionColor.a);
//	}
}