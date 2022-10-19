#pragma once

#include "Crystal/AppBase/IRenderer.h"

#include "CGLib/Graphics/Camera.h"
#include "CGLib/Shader/FrameBufferObject.h"
#include "Crystal/Renderer/TexRenderer.h"

#include "../FluidRenderer/ParticleDepthRenderer.h"
#include "../FluidRenderer/SSThicknessRenderer.h"
#include "../FluidRenderer/SSReflectionRenderer.h"
#include "../FluidRenderer/SSFluidRenderer.h"
#include "../FluidRenderer/BilateralFilterRenderer.h"
#include "../FluidRenderer/SSNormalRenderer.h"

namespace Crystal {
	namespace UI {

class World;

class Renderer : public Crystal::UI::IRenderer
{
public:
	explicit Renderer(World* world) :
		world(world)
	{}

	void init() override;

	void render(const int width, const int height) override;

private:
	World* world;

	struct Textures
	{
		Shader::TextureObject background;
		Shader::TextureObject depthTexture;
		Shader::TextureObject normalTexture;
		Shader::TextureObject filteredDepthTexture;
		Shader::TextureObject thicknessTexture;
		Shader::TextureObject absorptionTexture;
		Shader::TextureObject shadedTexture;
		Shader::TextureObject reflectedTexture;
		Shader::TextureObject refractedTexture;
		Shader::TextureObject texture;
	};

	struct Renderers
	{
		//Shader::SkyBoxRenderer skyBoxRenderer;
		Crystal::Renderer::ParticleDepthRenderer depth;
		Crystal::Renderer::SSThicknessRenderer thickness;
		Crystal::Renderer::BilateralFilterRenderer bilateralFilter;
		Crystal::Renderer::SSNormalRenderer normal;
		//SSFRReflectionRenderer reflectionRenderer;
		//SSFRRefractionRenderer refractionRenderer;
		//SSFRDeferredRenderer deferredRenderer;
		//SSFRAbsorptionRenderer absorptionRenderer;
		//SSFRFluidRenderer fluidRenderer;
		Crystal::Renderer::TexRenderer tex;
	};

	struct Buffer
	{
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelviewMatrix;
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject pointSize;
		Shader::VertexBufferObject uvec;
		Shader::VertexBufferObject vvec;
		Shader::VertexBufferObject wvec;
		int pointCount;
	};

	Buffer buffer;
	Textures textures;
	Renderers renderers;

	Shader::FrameBufferObject fbo;

private:
	void renderBackGround(const Graphics::Camera& camera);

	void renderDepth(const Graphics::Camera& camera);

	void filterDepth();

	void renderNormal(const Graphics::Camera& camera);

	void renderThickness(const Graphics::Camera& camera);

	void renderDeffered(const Graphics::Camera& camera);

	void renderReflection(const Graphics::Camera& camera);

	void renderRefraction(const Graphics::Camera& camera);

	void renderComposition(const Graphics::Camera& camera);

	void renderAbsorption(const Graphics::Camera& camera);
};

	}
}
