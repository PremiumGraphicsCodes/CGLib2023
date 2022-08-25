#pragma once

#include "glew.h"
#include <vector>

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shader {

class Uniform
{
public:
	Uniform() = default;

	explicit Uniform(const GLuint location) :
		location(location)
	{}

	void sendUniform(const Math::Matrix3df& matrix);

	void sendUniform(const Math::Matrix4df& matrix);

	void sendUniform(const Math::Vector3df& vector);

	void sendUniform(const int value);

	void sendUniform(const float value);

private:
	GLuint location;
};

	}
}