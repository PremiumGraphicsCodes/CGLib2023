#include "SSDefferedRenderer.h"

using namespace Crystal::Renderer;

using namespace Crystal::Math;
using namespace Crystal::Shader;

namespace {
	std::vector<float> toArray()
	{
		return{
			-1,  1,
			-1, -1,
			1, -1,
			1, 1
		};
	}

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

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint depthTex;
		GLuint normalTex;
		GLuint lightPos;
		GLuint lightAmbient;
		GLuint lightDiffuse;
		GLuint lightSpecular;
		GLuint materialAmbient;
		GLuint materialDiffuse;
		GLuint materialSpecular;
		GLuint materialShininess;
		GLuint eyePos;
	};

	struct VertexAttrLoc {
		GLuint position;
	};

	UniformLoc uniformLoc;
	VertexAttrLoc vaLoc;
}

void SSDefferedRenderer::link()
{
	uniformLoc.projectionMatrix = shader->findUniformLocation(::ProjectionMatrixLabel);

	uniformLoc.depthTex = shader->findUniformLocation(::DepthTexLabel);
	uniformLoc.normalTex = shader->findUniformLocation(::NormalTexLabel);

	uniformLoc.lightPos = shader->findUniformLocation(::LightPosLabel);
	uniformLoc.lightAmbient = shader->findUniformLocation(::LightAmbientLabel);
	uniformLoc.lightDiffuse = shader->findUniformLocation(::LightDiffuseLabel);
	uniformLoc.lightSpecular = shader->findUniformLocation(::LightSpecularLabel);

	uniformLoc.materialAmbient = shader->findUniformLocation(::MaterialAmbientLabel);
	uniformLoc.materialDiffuse = shader->findUniformLocation(::MaterialDiffuseLabel);
	uniformLoc.materialSpecular = shader->findUniformLocation(::MaterialSpecularLabel);
	uniformLoc.materialShininess = shader->findUniformLocation(::MaterialShininessLabel);

	uniformLoc.eyePos = shader->findUniformLocation(::EyePositionLabel);

	vaLoc.position = shader->findAttribLocation(::PositionLabel);
}

void SSDefferedRenderer::render()
{
	/*
	assert(GL_NO_ERROR == glGetError());

	const auto positions = ::toArray();

	shader->bind();

	TextureUnit texUnit(0, buffer.volumeTexture);

	Uniform texUniform(volumeTexLoc);
	texUniform.send(texUnit);

	VertexAttribute posAttr(vaLoc.position);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput("fragColor");

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
	*/
}
