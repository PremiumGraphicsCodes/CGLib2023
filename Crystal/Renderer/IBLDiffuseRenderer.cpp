#include "IBLDiffuseRenderer.h"
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
	constexpr auto cameraPosLabel = "camPos";
	constexpr auto fragColorLabel = "FragColor";

	struct AttributeLoc {
		GLuint position;
		GLuint normal;
	};
	AttributeLoc attrLoc;

	struct UniformLocs {
		GLuint projectionMatrix;
		GLuint modelMatrix;
		GLuint viewMatrix;
		GLuint albedo;
		GLuint metalic;
		GLuint ao;
		GLuint irradiance;
		GLuint eyePos;
	};
	UniformLocs uniforms;
}

void IBLDiffuseRenderer::link()
{
	attrLoc.position = shader->findAttribLocation(::positionLabel);
	attrLoc.normal = shader->findAttribLocation(::normalLabel);

	uniforms.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniforms.modelMatrix = shader->findUniformLocation(::modelMatrixLabel);
	uniforms.viewMatrix = shader->findUniformLocation(::viewMatrixLabel);

	uniforms.albedo = shader->findUniformLocation(::albedoLabel);
	uniforms.metalic = shader->findUniformLocation(::metalicLabel);
	uniforms.ao = shader->findUniformLocation(::ambientOcclusionLabel);
	uniforms.irradiance = shader->findUniformLocation(::irradianceMapLabel);
	uniforms.eyePos = shader->findUniformLocation(::cameraPosLabel);
}

void IBLDiffuseRenderer::render()
{
	shader->bind();
	shader->bindOutput(::fragColorLabel);

	/*
	TextureUnit texUnit(0, buffer.irradianceMapTex);

	Uniform irradiance(uniforms.irradiance);
	irradiance.send(texUnit);
	shader->sendUniform(::irradianceMapLabel, 0);

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelMatrixLabel, buffer.modelMatrix);
	shader->sendUniform(::viewMatrixLabel, buffer.viewMatrix);
	shader->sendUniform(::cameraPosLabel, buffer.eyePosition);

	shader->sendVertexAttribute3df(::positionLabel, *buffer.position);
	shader->sendVertexAttribute3df(::normalLabel, *buffer.normal);

	shader->sendUniform(::albedoLabel, buffer.albedo);
	shader->sendUniform(::metalicLabel, buffer.metalic);
	shader->sendUniform(::ambientOcclusionLabel, buffer.ao);

	buffer.position->bind();
	buffer.normal->bind();
	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::normalLabel);

	buffer.position->unbind();
	buffer.normal->unbind();

	buffer.irradianceMapTex->unbind();
	*/

	shader->unbind();
}