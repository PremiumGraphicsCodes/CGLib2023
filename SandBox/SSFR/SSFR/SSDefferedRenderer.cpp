#include "SSDefferedRenderer.h"

#include "CGLib/Shader/TextureUnit.h"

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
	assert(GL_NO_ERROR == glGetError());

	const auto positions = ::toArray();

	shader->bind();

	TextureUnit depthTexUnit(0, buffer.depthTexture);
	TextureUnit normalTexUnit(1, buffer.normalTexture);

	Uniform depthTexUniform(uniformLoc.depthTex);
	depthTexUniform.send(depthTexUnit);
	Uniform normalTexUniform(uniformLoc.normalTex);
	normalTexUniform.send(normalTexUnit);

	Uniform projection(uniformLoc.projectionMatrix);
	Uniform eyePos(uniformLoc.eyePos);

	Uniform lightPos(uniformLoc.lightPos);
	Uniform lightAmbient(uniformLoc.lightAmbient);
	Uniform lightDiffuse(uniformLoc.lightDiffuse);
	Uniform lightSpecular(uniformLoc.lightSpecular);

	Uniform materialAmbient(uniformLoc.materialAmbient);
	Uniform materialDiffuse(uniformLoc.materialDiffuse);
	Uniform materialSpecular(uniformLoc.materialSpecular);
	Uniform materialShininess(uniformLoc.materialShininess);

	projection.send(buffer.projectionMatrix);
	eyePos.send(buffer.eyePosition);

	lightPos.send(buffer.lights[0].pos);
	lightAmbient.send(buffer.lights[0].ambient);
	lightDiffuse.send(buffer.lights[0].diffuse);
	lightSpecular.send(buffer.lights[0].specular);

	materialAmbient.send(buffer.materials[0].ambient);
	materialDiffuse.send(buffer.materials[0].diffuse);
	materialSpecular.send(buffer.materials[0].specular);
	materialShininess.send(buffer.materials[0].shininess);
	
	VertexAttribute posAttr(vaLoc.position);
	posAttr.sendVertexAttribute2df(positions);

	shader->bindOutput("fragColor");

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}