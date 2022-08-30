#include "DFAlbedoRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

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
	shader->bind();
	shader->bindOutput("fragColor");

	shader->enable(GL_DEPTH_TEST);

	Uniform projectionMatrix(uniforms.projectionMatrix);
	Uniform modelviewMatrix(uniforms.modelviewMatrix);

	projectionMatrix.send(buffer.projectionMatrix);
	modelviewMatrix.send(buffer.modelViewMatrix);

	VertexAttribute position(attributes.position);
	VertexAttribute texCoord(attributes.texCoord);
	position.sendVertexAttribute3df(*buffer.position);
	texCoord.sendVertexAttribute2df(*buffer.texCoord);

	for (const auto& fg : buffer.faceGroups) {
		TextureUnit texUnit(0, fg.texture);
		Uniform tex(uniforms.texture);
		tex.send(texUnit);
		shader->drawTriangles(fg.indices);
	}

	shader->disable(GL_DEPTH_TEST);


	shader->unbind();
}