#version 150
in vec3 vuvec;
in vec3 vvvec;
in vec3 vwvec;
in vec4 vPosition;
//in float vSize;
out vec4 fragColor;
uniform mat4 modelviewMatrix;
uniform mat4 projectionMatrix;
bool isInside(vec2 coord) {
	float dist = dot(coord, coord);
	return dist < 1.0;
}
vec3 toSphereCoord(vec3 coord, vec3 uvec, vec3 vvec, vec3 wvec) {
	mat3 m = mat3(uvec, vvec, wvec);
	vec3 v = coord * inverse(m);
	return v;
}
bool isInside(vec3 sCoord) {
	float dist = dot(sCoord, sCoord);
	return dist < 1.0;
}
void main(void) {
	vec2 coord = gl_PointCoord * 2.0 - 1.0;
	vec3 coord3 = mat3(modelviewMatrix) * vec3(coord, 0);
	vec3 sCoord = toSphereCoord(coord3, vuvec, vvvec, vwvec);
	if(isInside(sCoord)) {
		vec4 pixelPos = vPosition + vec4(sCoord, 1.0);
		vec4 clipSpacePos = projectionMatrix * pixelPos;
		float depth = clipSpacePos.z / clipSpacePos.w;
		fragColor.rgb = vec3(depth);
//		fragColor.rgb = coord3.xyz;// vec3(1.0);
		fragColor.a = 1.0;
//		gl_FragDepth = depth;
	} else {
		discard;
	}
}