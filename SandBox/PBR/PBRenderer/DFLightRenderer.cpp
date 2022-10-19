#include "DFLightRenderer.h"

#include "CGLib/Math/Box2d.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto positionTextureLabel = "positionTexture";
	constexpr auto normalTextureLabel = "normalTexture";
	constexpr auto colorTextureLabel = "colorTexture";
	constexpr auto invModelViewMatrixLabel = "invModelViewMatrix";
	constexpr auto invProjectionMatrixLabel = "invProjectionMatrix";
	constexpr auto invNormalMatrixLabel = "invNormalMatrix";

	struct UniformLoc {
		GLuint invProjectionMatrix;
		GLuint invModelviewMatrix;
		GLuint invNormalMatrix;
		GLuint positionTexture;
		GLuint normalTexture;
		GLuint colorTexture;
		GLuint lightPos;
		GLuint lightColor;
	};

	UniformLoc uniforms;

	struct VertexAttrLoc {
		GLuint position;
	};
	VertexAttrLoc va;
}

void DFLightRenderer::link()
{
	uniforms.invProjectionMatrix = shader->findUniformLocation(::invProjectionMatrixLabel);
	uniforms.invModelviewMatrix = shader->findUniformLocation(::invModelViewMatrixLabel);
	uniforms.invNormalMatrix = shader->findUniformLocation(::invNormalMatrixLabel);
	uniforms.positionTexture = shader->findUniformLocation(::positionTextureLabel);
	uniforms.normalTexture = shader->findUniformLocation(::normalTextureLabel);
	uniforms.colorTexture = shader->findUniformLocation(::colorTextureLabel);
	uniforms.lightPos = shader->findUniformLocation("light.position");
	uniforms.lightColor = shader->findUniformLocation("light.color");

	va.position = shader->findAttribLocation(::positionLabel);
}

namespace {
	std::vector<float> toArray(const Box2d<float>& box)
	{
		const auto min = box.getMin();
		const auto max = box.getMax();
		return{
			min.x, max.y,
			min.x, min.y,
			max.x, min.y,
			max.x, max.y
		};
	}
}

void DFLightRenderer::render()
{
	/*
	const Box2d<float> box(Vector2df(-1.0, -1.0), Vector2df(1.0, 1.0));
	const auto& positions = ::toArray(box);

	shader->bind();
	shader->bindOutput("fragColor", 0);

	shader->sendUniform(::invProjectionMatrixLabel, buffer.invProjectionMatrix);
	shader->sendUniform(::invModelViewMatrixLabel, buffer.invModelViewMatrix);
	shader->sendUniform(::invNormalMatrixLabel, buffer.invNormalMatrix);
	shader->sendUniform("light.position", buffer.lightPosition);
	shader->sendUniform("light.color", buffer.lightColor);

	buffer.positionTex->bind(0);
	buffer.normalTex->bind(1);
	buffer.albedoTex->bind(2);

	shader->sendUniform(::positionTextureLabel, 0);
	shader->sendUniform(::normalTextureLabel, 1);
	shader->sendUniform(::colorTextureLabel, *buffer.albedoTex, 2);

	glEnableVertexAttribArray(0);
	shader->sendVertexAttribute2df(::positionLabel, positions);
	shader->drawQuads(positions.size() / 2);
	glDisableVertexAttribArray(0);

	buffer.positionTex->unbind();
	buffer.normalTex->unbind();
	buffer.albedoTex->unbind();

	shader->unbind();
	*/
}