#include "SSDefferedRenderer.h"

using namespace Crystal::Renderer;

using namespace Crystal::Math;
using namespace Crystal::Shader;

namespace {
	constexpr auto ProjectionMatrixLabel = "projectionMatrix";

	constexpr auto DepthTexLabel = "depthTex";
	constexpr auto NormalTexLabel = "normalTex";

	constexpr auto LightPosLabel = "light.position";
	constexpr auto LightAmbientLabel = "light.La";
	constexpr auto LightDiffuseLabel = "light.Ld";
	constexpr auto LightSpecularLabel = "light.Ls";

	constexpr auto MaterialAmbientLabel = "material.Ka";
	constexpr auto MaterialDiffuseLabel = "material.Kd";
	constexpr auto MaterialSpecularLabel = "material.Ks";
	constexpr auto MaterialShininessLabel = "material.shininess";

	constexpr auto EyePositionLabel = "eyePosition";
	constexpr auto PositionLabel = "position";
}

void SSDefferedRenderer::link()
{
	shader->findUniformLocation(::ProjectionMatrixLabel);

	shader->findUniformLocation(::DepthTexLabel);
	shader->findUniformLocation(::NormalTexLabel);

	shader->findUniformLocation(::LightPosLabel);
	shader->findUniformLocation(::LightAmbientLabel);
	shader->findUniformLocation(::LightDiffuseLabel);
	shader->findUniformLocation(::LightSpecularLabel);

	shader->findUniformLocation(::MaterialAmbientLabel);
	shader->findUniformLocation(::MaterialDiffuseLabel);
	shader->findUniformLocation(::MaterialSpecularLabel);
	shader->findUniformLocation(::MaterialShininessLabel);

	shader->findUniformLocation(::EyePositionLabel);

	shader->findAttribLocation(::PositionLabel);
}

void SSDefferedRenderer::render()
{
}
