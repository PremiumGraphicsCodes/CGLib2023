#version 150
uniform sampler2D depthTex;
uniform mat4 projectionMatrix;
uniform float texelSizeW;
uniform float texelSizeH;
in vec2 texCoord;
out vec4 fragColor;
vec3 uvToEye(vec2 tCoord, float depth) {
	vec4 clippingPosition = vec4(tCoord, depth, 1.0);
	vec4 viewPosition = inverse(projectionMatrix) * clippingPosition;
    return viewPosition.xyz / viewPosition.w;
}
float getDepth(vec2 tCoord){
	return texture2D(depthTex, tCoord).r;
}
vec3 getEyePosition(vec2 texCoord){
	float depth = getDepth(texCoord);
	return uvToEye(texCoord, depth);
}
void main(void) {
	float depth = getDepth(texCoord);
	if(depth < 0.01) {
		fragColor.rgba = vec4(0.0, 0.0, 0.0, 1.0);
		//fragColor.rgba = texture2D(depthTex, texCoord);
		return;
	}
    vec3 eyePosition = getEyePosition(texCoord);
	vec3 ddx1 = getEyePosition(texCoord + vec2(texelSizeW, 0)) - eyePosition;
	vec3 ddx2 = eyePosition - getEyePosition(texCoord-vec2(texelSizeW, 0));
	if(abs(ddx1.z) > abs(ddx2.z)) {
		ddx1 = ddx2;
	}
	vec3 ddy1 = getEyePosition(texCoord + vec2(0, texelSizeH)) - eyePosition;
	vec3 ddy2 = vec3(texCoord, 0.0) - getEyePosition(texCoord - vec2(0, texelSizeH));
	if(abs(ddy1.z) > abs(ddy2.z)) {
		ddy1 = ddy2;
	}
	vec3 normal = normalize( cross(ddx1, ddy1) );
	fragColor.rgb = normal;
	//	fragColor.rg = texCoord.xy;
	fragColor.a = 1.0;
}