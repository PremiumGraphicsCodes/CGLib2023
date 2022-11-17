#pragma once
#include "World.h"
#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/Renderer/PointRenderer.h"
#include "Crystal/Renderer/LineRenderer.h"
#include "Crystal/Renderer/TriangleRenderer.h"
#include "Crystal/Renderer/TexRenderer.h"
#include "CGLib/Shader/FrameBufferObject.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal{
	namespace UI {

class Renderer : public Crystal::UI::IRenderer
{
public:
	enum class Target
	{
		Main,
		Id,
	};

	explicit Renderer(World* world);

	void setTarget(const Target t) { this->target = t; }

	void init() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

	Crystal::Renderer::PointRenderer* getPointRenderer() { return &renderers.point; }

	Crystal::Renderer::LineRenderer* getLineRenderer() { return &renderers.line; }

	Crystal::Renderer::TriangleRenderer* getTriangleRenderer() { return &renderers.triangle; }

	Shader::TextureObject* getIdTexture() { return &textures.id; }

private:
	World* world;
	Target target;
	
	struct Renderers {
		Crystal::Renderer::PointRenderer point;
		Crystal::Renderer::LineRenderer line;
		Crystal::Renderer::TriangleRenderer triangle;
		Crystal::Renderer::TexRenderer tex;
	};
	Renderers renderers;

	struct Textures {
		Shader::TextureObject main;
		Shader::TextureObject id;
	};
	Textures textures;
	Shader::FrameBufferObject fbo;

	void renderMain(const Graphics::Camera& camera);

	void renderId(const Graphics::Camera& camera);
};

	}
}
