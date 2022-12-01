#pragma once

#include "IRenderer.h"
#include "CGLib/Math/Matrix4d.h"
#include "CGLib/Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Renderer {

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
		GLfloat lineWidth = 1.0f;
	};

	void link() override;

	void render() override;

	Buffer buffer;
};

	}
}