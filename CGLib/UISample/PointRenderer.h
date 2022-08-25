#pragma once

#include "IRenderer.h"
#include "../Math/Matrix4d.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/VertexBufferObject.h"
#include <memory>

namespace Crystal {
	namespace UI {

class PointRenderer : public IRenderer
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

	void link() override;

	void render() override;

	Buffer buffer;

};

	}
}