#include "SkyBoxShader.h"
#include "CGLib/Graphics/ImageFileReader.h"
#include "CGLib/Shader/ShaderBuilder.h"
#include "Crystal/Renderer/Renderer/SkyBoxShaderSource.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	bool readCubeMap(CubeMapTextureObject& cubeMap)
	{
		std::array<Imageuc, 6> images;

		ImageFileReader reader;
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posx.jpg")) {
			return false;
		}
		images[0] = reader.toImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/negx.jpg")) {
			return false;
		}
		images[1] = reader.toImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posy.jpg")) {
			return false;
		}
		images[2] = reader.toImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/negy.jpg")) {
			return false;
		}
		images[3] = reader.toImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posz.jpg")) {
			return false;
		}
		images[4] = reader.toImage();
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/negz.jpg")) {
			return false;
		}
		images[5] = reader.toImage();
		cubeMap.create();
		cubeMap.send(images);
		return true;
	}
}

void SkyBoxShader::build()
{
	ShaderBuilder builder;
	builder.build(SkyBoxShaderSource::getVertexShaderSource(), SkyBoxShaderSource::getFragmentShaderSource());
	auto shader = builder.getShader();
	skyBoxRenderer.setShader(std::move(shader));
	skyBoxRenderer.link();

	this->cubeMapTexture = std::make_unique<CubeMapTextureObject>();
	readCubeMap(*this->cubeMapTexture);
}

void SkyBoxShader::render(const Camera& camera, const int width, const int height)
{
	{

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skyBoxRenderer.buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
		skyBoxRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		skyBoxRenderer.buffer.cubeMapTexture = this->cubeMapTexture.get();

		skyBoxRenderer.render();

	}
}