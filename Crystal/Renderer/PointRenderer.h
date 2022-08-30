#pragma once

#include "IRenderer.h"

#include "CGLib/Shader/VertexBufferObject.h"
#include "CGLib/Math/Matrix4d.h"

namespace Crystal {
	namespace Renderer {

class PointRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* size;
		Shader::VertexBufferObject* color;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelViewMatrix;
		int count = 0;
	};

	void link() override;

	void render() override;

private:
};

	}
}