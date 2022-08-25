#pragma once

#include "../Graphics/Camera.h"

#include "PointRenderer.h"
#include "TexRenderer.h"

namespace Crystal {
	namespace UI {

class ScreenRenderer
{
public:
	ScreenRenderer();

	enum RenderingType {
		Point,
		Tex,
	};

	void setActiveRenderer(const RenderingType type);

	void build();

	void render(const int width, const int height);

private:
	Crystal::UI::PointRenderer renderer;
	Crystal::UI::TexRenderer texRenderer;
	Crystal::UI::IRenderer* activeRenderer;

	Crystal::Shader::VertexBufferObject positionVBO;
	Crystal::Shader::VertexBufferObject colorVBO;
	Crystal::Shader::VertexBufferObject sizeVBO;

	Crystal::Shader::TextureObject tex;

	Graphics::Camera camera;
};

	}
}
