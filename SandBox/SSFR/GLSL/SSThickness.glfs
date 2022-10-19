#version 150
in vec3 vuvec;
in vec3 vvvec;
in vec3 vwvec;
out vec4 fragColor;
uniform mat4 modelviewMatrix;
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
	if(!isInside(sCoord)) {
		discard;
	}
	float dist = sqrt(1.0 - dot(sCoord, sCoord));
	fragColor = vec4(dist * 0.1);//vec4(0.25 * sCoord.z);
}