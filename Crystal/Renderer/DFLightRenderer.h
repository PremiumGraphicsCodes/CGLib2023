#pragma once

#include "IRenderer.h"

#include "CGLib/Math/Matrix3d.h"
#include "CGLib/Math/Matrix4d.h"

#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace Renderer {

class DFLightRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::TextureObject* positionTex;
		Shader::TextureObject* normalTex;
		Shader::TextureObject* albedoTex;
		Math::Matrix4df invModelViewMatrix;
		Math::Matrix4df invProjectionMatrix;
		Math::Matrix3df invNormalMatrix;
		Math::Vector3df lightPosition;
		Math::Vector3df lightColor;
	};

	void link();

	void render();

	Buffer buffer;

private:
};

	}
}