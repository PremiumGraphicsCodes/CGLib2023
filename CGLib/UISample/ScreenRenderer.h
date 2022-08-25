#pragma once

#include "../Graphics/Camera.h"

#include "PointRenderer.h"
#include "LineRenderer.h"
#include "TexRenderer.h"

namespace Crystal {
	namespace UI {

class ScreenRenderer
{
public:
	ScreenRenderer();

	enum RenderingType {
		Point,
		Line,
		Tex,
	};

	void setActiveRenderer(const RenderingType type);

	void build();

	void render(const int width, const int height);

private:
	struct Renderers
	{
		Crystal::UI::PointRenderer pointRenderer;
		Crystal::UI::LineRenderer lineRenderer;
		Crystal::UI::TexRenderer texRenderer;
	};
	Renderers renderers;

	Crystal::UI::IRenderer* activeRenderer;

	Crystal::Shader::VertexBufferObject positionVBO;
	Crystal::Shader::VertexBufferObject colorVBO;
	Crystal::Shader::VertexBufferObject sizeVBO;
	Crystal::Shader::TextureObject tex;

	Graphics::Camera camera;
};

	}
}
