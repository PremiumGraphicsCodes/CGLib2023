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

	void send(const Math::Matrix3df& matrix);

	void send(const Math::Matrix4df& matrix);

	void send(const Math::Vector3df& vector);

	void send(const int value);

	void send(const float value);

private:
	GLuint location;
};

	}
}