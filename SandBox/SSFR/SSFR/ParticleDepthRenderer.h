#pragma once

#include "Crystal/Renderer/Renderer/IRenderer.h"

#include "CGLib/Shader/VertexBufferObject.h"
#include "CGLib/Math/Matrix4d.h"

namespace Crystal {
	namespace Renderer {

class ParticleDepthRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* size;
		Shader::VertexBufferObject* uvec;
		Shader::VertexBufferObject* vvec;
		Shader::VertexBufferObject* wvec;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		int count = 0;
	};

	void link() override;

	void render() override;

	Buffer buffer;
private:
};

	}
}