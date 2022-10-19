#include "IBLSpecularRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto modelMatrixLabel = "model";
	constexpr auto viewMatrixLabel = "view";

	constexpr auto positionLabel = "aPos";
	constexpr auto normalLabel = "aNormal";

	constexpr auto albedoLabel = "albedo";
	constexpr auto metalicLabel = "metallic";
	constexpr auto ambientOcclusionLabel = "ao";
	constexpr auto irradianceMapLabel = "irradianceMap";
	constexpr auto importanceMapLabel = "prefilterMap";
	constexpr auto brdfLutTexLabel = "brdfLUT";

	constexpr auto cameraPosLabel = "camPos";
	constexpr auto fragColorLabel = "FragColor";

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint modelMatrix;
		GLuint viewMatrix;
		GLuint albedo;
		GLuint metalic;
		GLuint ao;
		GLuint irradiance;
		GLuint importance;
		GLuint brdfLutTex;
		GLuint eyePos;
	};
	UniformLoc uniforms;

	struct VertexAttrLoc {
		GLuint position;
		GLuint normal;
	};
	VertexAttrLoc attrs;
}

IBLSpecularRenderer::IBLSpecularRenderer()
{
}

void IBLSpecularRenderer::link()
{
	attrs.position = shader->findAttribLocation(::positionLabel);
	attrs.normal = shader->findAttribLocation(::normalLabel);

	uniforms.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniforms.modelMatrix = shader->findUniformLocation(::modelMatrixLabel);
	uniforms.viewMatrix = shader->findUniformLocation(::viewMatrixLabel);

	uniforms.albedo = shader->findUniformLocation(::albedoLabel);
	uniforms.metalic = shader->findUniformLocation(::metalicLabel);
	uniforms.ao = shader->findUniformLocation(::ambientOcclusionLabel);
	uniforms.irradiance = shader->findUniformLocation(::irradianceMapLabel);
	uniforms.importance = shader->findUniformLocation(::importanceMapLabel);
	uniforms.brdfLutTex = shader->findUniformLocation(::brdfLutTexLabel);
	uniforms.eyePos = shader->findUniformLocation(::cameraPosLabel);
}

void IBLSpecularRenderer::render()
{
	shader->bind();
	shader->bindOutput(::fragColorLabel);

	TextureUnit irradianceTex(0, buffer.irradianceMapTex);
	TextureUnit importanceTex(1, buffer.importanceMapTex);
	TextureUnit lutTex(2, buffer.brdfLutTex);

	Uniform irradianceTexUniform(uniforms.irradiance);
	irradianceTexUniform.send(irradianceTex);

	Uniform importanceTexUniform(uniforms.importance);
	importanceTexUniform.send(importanceTex);

	Uniform lutTexUniform(uniforms.brdfLutTex);
	lutTexUniform.send(lutTex);

	Uniform projectionMatrix(uniforms.projectionMatrix);
	projectionMatrix.send(buffer.projectionMatrix);

	Uniform modelMatrix(uniforms.modelMatrix);
	modelMatrix.send(buffer.modelMatrix);

	Uniform viewMatrix(uniforms.viewMatrix);
	viewMatrix.send(buffer.viewMatrix);

	Uniform eyePos(uniforms.eyePos);
	eyePos.send(buffer.eyePosition);

	Uniform albedo(uniforms.albedo);
	albedo.send(buffer.albedo);

	Uniform metaric(uniforms.metalic);
	metaric.send(buffer.metalic);

	Uniform ao(uniforms.ao);
	ao.send(buffer.ao);

	VertexAttribute positions(attrs.position);
	positions.sendVertexAttribute3df(*buffer.position);

	VertexAttribute normals(attrs.normal);
	normals.sendVertexAttribute3df(*buffer.normal);

	shader->drawTriangles(buffer.indices);

	shader->unbind();
}