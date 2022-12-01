#pragma once

#include "Crystal/Renderer/Renderer/IRenderer.h"

#include "CGLib/Math/Matrix3d.h"
#include "CGLib/Math/Matrix4d.h"
#include "CGLib/Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Renderer {

class DFGeometryRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* normal;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelViewMatrix;
		Math::Matrix3df normalMatrix;
		std::vector<unsigned int> indices;
	};

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}