#pragma once

#include "../Graphics/Camera.h"

#include "PointRenderer.h"
#include "LineRenderer.h"
#include "TriangleRenderer.h"
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
		Triangle,
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
		Crystal::UI::TriangleRenderer triangleRenderer;
		Crystal::UI::TexRenderer texRenderer;
	};

	struct Buffers
	{
		Crystal::Shader::VertexBufferObject positionVBO;
		Crystal::Shader::VertexBufferObject colorVBO;
		Crystal::Shader::VertexBufferObject sizeVBO;
	};

	Renderers renderers;
	Buffers buffers;
	IRenderer* activeRenderer;
	Crystal::Shader::TextureObject tex;
	Graphics::Camera camera;
};

	}
}
