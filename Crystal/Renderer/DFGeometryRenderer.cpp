#include "DFGeometryRenderer.h"

#include "CGLib/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto normalMatrixLabel = "normalMatrix";
	constexpr auto positionLabel = "position";
	constexpr auto normalLabel = "normal";

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint normalMatrix;
	};
	UniformLoc uniforms;

	struct AttribLoc {
		GLuint position;
		GLuint normal;
	};
	AttribLoc attributes;
}

void DFGeometryRenderer::link()
{
	uniforms.projectionMatrix = this->shader->findUniformLocation(::projectionMatrixLabel);
	uniforms.modelviewMatrix = this->shader->findUniformLocation(::modelViewMatrixLabel);
	uniforms.normalMatrix = this->shader->findUniformLocation(::normalMatrixLabel);

	attributes.position = this->shader->findAttribLocation(::positionLabel);
	attributes.normal = this->shader->findAttribLocation(::normalLabel);
}

void DFGeometryRenderer::render()
{
	/*
	shader->bind();
	shader->bindOutput("gPosition", 0);
	shader->bindOutput("gNormal", 1);

	shader->enableDepthTest();


	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);
	shader->sendUniform(::normalMatrixLabel, buffer.normalMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute3df(::normalLabel, buffer.normal);

	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::normalLabel);

	shader->disableDepthTest();


	shader->unbind();
	*/
}