#pragma once

#include "Crystal/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

class SSThicknessRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelviewMatrix;
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* pointSize;
		Shader::VertexBufferObject* uvec;
		Shader::VertexBufferObject* vvec;
		Shader::VertexBufferObject* wvec;
		int pointCount;
	};

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}