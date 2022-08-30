#include "DFAlbedoRenderer.h"

#include <sstream>

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto positionLabel = "position";
	constexpr auto texCoordLabel = "texCoord";
	constexpr auto textureLabel = "texture";

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint texture;
	};
	UniformLoc uniforms;

	struct VertexAttrLoc {
		GLuint position;
		GLuint texCoord;
	};
	VertexAttrLoc attributes;
}

void DFAlbedoRenderer::link()
{
	uniforms.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniforms.modelviewMatrix = shader->findUniformLocation(::modelViewMatrixLabel);
	uniforms.texture = shader->findUniformLocation(::textureLabel);

	attributes.position = shader->findAttribLocation(::positionLabel);
	attributes.texCoord = shader->findAttribLocation(::texCoordLabel);
}

void DFAlbedoRenderer::render()
{
	/*
	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();


	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute2df(::texCoordLabel, buffer.texCoord);

	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::texCoordLabel);

	for (const auto& fg : buffer.faceGroups) {
		shader->sendUniform(::textureLabel, *fg.texture, 0);
		fg.texture->bind(0);
		shader->drawTriangles(fg.indices);
		fg.texture->unbind();
	}

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::texCoordLabel);

	shader->disableDepthTest();


	shader->unbind();
	*/
}