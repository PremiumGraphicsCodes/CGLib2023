#pragma once

#include "IRenderer.h"
#include "../Math/Matrix4d.h"
#include "../Shader/VertexBufferObject.h"
#include <memory>

namespace Crystal {
	namespace UI {

class LineRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* color;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		std::vector<unsigned int> indices;
		GLfloat lineWidth;
	};

	void link() override;

	void render() override;

	Buffer buffer;
};

	}
}