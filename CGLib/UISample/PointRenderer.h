#pragma once

#include "../Math/Matrix4d.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/VertexBufferObject.h"
#include <memory>

namespace Crystal {
	namespace UI {

class PointRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* size;
		Shader::VertexBufferObject* color;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		int count = 0;
	};

	void build();

	void render();

	Buffer buffer;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}