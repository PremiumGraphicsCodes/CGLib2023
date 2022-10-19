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

	TextureUnit texUnit(0, buffer.irradianceMapTex);

	Uniform irradiance(uniforms.irradiance);
	irradiance.send(texUnit);

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

	Uniform metalic(uniforms.metalic);
	metalic.send(buffer.metalic);

	Uniform ao(uniforms.ao);
	ao.send(buffer.ao);

	VertexAttribute positions(attrLoc.position);
	positions.sendVertexAttribute3df(*buffer.position);

	VertexAttribute normals(attrLoc.normal);
	normals.sendVertexAttribute3df(*buffer.normal);

	shader->drawTriangles(buffer.indices);

	shader->unbind();
}