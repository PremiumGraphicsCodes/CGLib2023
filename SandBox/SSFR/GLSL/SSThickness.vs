#version 150
in vec3 position;
in float pointSize;
in vec3 uvec;
in vec3 vvec;
in vec3 wvec;
out vec3 vuvec;
out vec3 vvvec;
out vec3 vwvec;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	gl_PointSize = pointSize / gl_Position.w;
	vuvec = uvec;
	vvvec = vvec;
	vwvec = wvec;
}