#pragma once

#include "CGLib/Shader/ShaderObject.h"
#include "CGLib/Shader/VertexBufferObject.h"
#include "Crystal/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

class PBLightRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* normal;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelMatrix;
		Math::Matrix4dd viewMatrix;
		Math::Vector3df eyePosition;

		Math::Vector3df albedo;
		float metalic;
		float roughness;
		float ao;

		Math::Vector3df lightPosition;
		Math::Vector3df lightColor;

		std::vector<unsigned int> indices;
	};

	PBLightRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}