#include "Uniform.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;

void Uniform::send(const Matrix3df& matrix)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Uniform::send(const Matrix4df& matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Uniform::send(const Vector3df& v)
{
	glUniform3fv(location, 1, &v[0]);
}

void Uniform::send(const int value)
{
	glUniform1i(location, value);
}

void Uniform::send(const float value)
{
	glUniform1f(location, value);
}
