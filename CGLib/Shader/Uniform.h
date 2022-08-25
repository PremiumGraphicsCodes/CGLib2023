#pragma once

#include "glew.h"
#include <vector>

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class TextureUnit;

class Uniform : private UnCopyable
{
public:
	explicit Uniform(const GLuint location) :
		location(location)
	{}

	void send(const Math::Matrix3df& matrix);

	void send(const Math::Matrix4df& matrix);

	void send(const Math::Vector3df& vector);

	void send(const int value);

	void send(const float value);

	void send(const TextureUnit& texUnit);

private:
	GLuint location;
};

	}
}