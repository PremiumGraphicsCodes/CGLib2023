#version 150
in vec3 position;
in float pointSize;
in vec3 uvec;
in vec3 vvec;
in vec3 wvec;
out vec3 vuvec;
out vec3 vvvec;
out vec3 vwvec;
out vec4 vPosition;
//out float vSize;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	gl_PointSize = pointSize / gl_Position.w;
	vPosition = modelviewMatrix * vec4(position, 1.0);
//	vSize = pointSize;
	vuvec = uvec;
	vvvec = vvec;
	vwvec = wvec;
}