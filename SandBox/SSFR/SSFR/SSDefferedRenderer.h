#pragma once

#include "Crystal/Renderer/Renderer/IRenderer.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class SSDefferedRenderer : public IRenderer
{
public:
	struct Light {
		Math::Vector3df pos;
		Math::Vector3df ambient;
		Math::Vector3df specular;
		Math::Vector3df diffuse;
	};

	struct Material {
		Math::Vector3df ambient;
		Math::Vector3df specular;
		Math::Vector3df diffuse;
		float shininess;
	};

	struct Buffer {
		Shader::TextureObject* depthTexture;
		Shader::TextureObject* normalTexture;
		Math::Vector3df eyePosition;
		Math::Matrix4df projectionMatrix;
		std::vector<Light> lights;
		std::vector<Material> materials;
	};

	void link() override;

	void render() override;

	Buffer buffer;
};

	}
}