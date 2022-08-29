#include "SkyBoxRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto cubeMapTexLabel = "cubeMapTex";
	constexpr auto fragColorLabel = "fragColor";

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint cubeMapTex;
	};

	struct AttribLoc {
		GLuint position;
	};

	UniformLoc uniforms;
	AttribLoc attributes;

	std::vector<float> positions = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

}

SkyBoxRenderer::SkyBoxRenderer()
{
}

void SkyBoxRenderer::link()
{
	uniforms.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniforms.modelviewMatrix = shader->findUniformLocation(::modelViewMatrixLabel);
	uniforms.cubeMapTex = shader->findUniformLocation(::cubeMapTexLabel);

	attributes.position = shader->findAttribLocation(::positionLabel);
}

void SkyBoxRenderer::render()
{
	/*
	shader->bind();


	shader->enable(GL_DEPTH_TEST);

	TextureUnit texUnit(0, *buffer.cubeMapTexture);

	Uniform projectionMatrix(uniforms.projectionMatrix);
	Uniform modelviewMatrix(uniforms.modelviewMatrix);
	Uniform cubeMapTex(uniforms.cubeMapTex);

	Attr

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	buffer.cubeMapTexture->bind(0);

	shader->sendUniform(cubeMapTexLabel, 0);

	shader->sendVertexAttribute3df(::positionLabel, positions);

	glEnableVertexAttribArray(0);
	shader->drawTriangles(positions.size() / 3);
	glDisableVertexAttribArray(0);

	buffer.cubeMapTexture->unbind();

	shader->bindOutput(::fragColorLabel);

	shader->unbind();

	shader->disable(GL_DEPTH_TEST);

	assert(GL_NO_ERROR == glGetError());
	*/
}