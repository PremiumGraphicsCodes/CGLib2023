#pragma once

#include "CGLib/Shader/TextureObject.h"
#include "CGLib/Shader/VertexBufferObject.h"
#include "Crystal/Renderer/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

class DFAlbedoRenderer : public IRenderer
{
public:
	struct Buffer
	{
		struct FaceGroup {
			Shader::TextureObject* texture;
			std::vector<unsigned int> indices;
		};

		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* texCoord;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		std::vector<FaceGroup> faceGroups;
	};

	virtual void link() override;

	virtual void render() override;

	Buffer buffer;
private:
};

	}
}