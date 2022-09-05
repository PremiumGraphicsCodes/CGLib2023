#include "IBLShader.h"
#include "CGLib/Shader/ShaderObject.h"
#include "CGLib/Shader/ShaderBuilder.h"
//#include "../CrystalRenderer/HDRImage.h"

#include "CGLib/Graphics/ImageFileReader.h"

#include "CGLib/ThirdParty/glm-0.9.9.8/glm/gtc/matrix_transform.hpp"

#include <filesystem>
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace
{
	void sendHDRTexture(const Imagef& hdr, TextureObject& hdrTex)
	{
		hdrTex.bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, hdr.getWidth(), hdr.getHeight(), 0, GL_RGBA, GL_FLOAT, hdr.getValues().data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		hdrTex.unbind();
	}

	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};

}

void IBLShader::build()
{
	ImageFileReader reader;
	Imagef hdr;
	reader.read("../../ThirdParty/hdr/newport_loft.hdr");
	textures.hdrTex.create();
	sendHDRTexture(hdr, textures.hdrTex);

	buffers.rbo.create();

	{
		std::array<Graphics::Imageuc, 6> images;
		for (int i = 0; i < 6; ++i) {
			Graphics::Imageuc im(512, 512);
			images[i] = im;
		}
		textures.cubeMapTex.create();
		textures.cubeMapTex.send(images);
	}

	textures.irradianceTex.create();
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures.irradianceTex.getHandle());
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	textures.irradianceTex.unbind();

	ShaderBuilder shaderBuilder;

	shaderBuilder.buildFromFile("../GLSL/CubeMap.vs", "../GLSL/CubeMap.fs");
	renderers.cubeMapRenderer.setShader(shaderBuilder.getShader());
	renderers.cubeMapRenderer.link();

	shaderBuilder.buildFromFile("../GLSL/Irradiance.vs", "../GLSL/Irradiance.fs");
	renderers.irradianceRenderer.setShader(shaderBuilder.getShader());
	renderers.irradianceRenderer.link();

	shaderBuilder.buildFromFile("../GLSL/IBLDiffuse.vs", "../GLSL/IBLDiffuse.fs");
	renderers.diffuseRenderer.setShader(shaderBuilder.getShader());
	renderers.diffuseRenderer.link();

	shaderBuilder.buildFromFile("../GLSL/BRDFLUT.vs", "../GLSL/BRDFLUT.fs");
	renderers.brdfLutRenderer.setShader(shaderBuilder.getShader());
	renderers.brdfLutRenderer.link();

	/*
	{
		auto shader = shaderBuilder.build("../GLSL/Importance.vs", "../GLSL/Importance.fs");
		renderers.importanceRenderer.setShader(std::move(shader));
		renderers.importanceRenderer.link();
	}

	{
		auto shader = shaderBuilder.build("../GLSL/IBLSpecular.vs", "../GLSL/IBLSpecular.fs");
		renderers.specularRenderer.setShader(std::move(shader));
		renderers.specularRenderer.link();
	}

	{
		auto shader = shaderBuilder.build("../GLSL/SkyBox.vs", "../GLSL/SkyBox.fs");
		renderers.skyBoxRenderer.setShader(std::move(shader));
		renderers.skyBoxRenderer.link();
	}
	*/

	/*
	{
		positions.add(Vector3dd(0.0, 0.0, 0.0));
		positions.add(Vector3dd(1.0, 0.0, 0.0));
		positions.add(Vector3dd(1.0, 1.0, 0.0));
		positions.add(Vector3dd(0.0, 1.0, 0.0));

		normals.add(Vector3dd(0, 0, 1));
		normals.add(Vector3dd(0, 0, 1));
		normals.add(Vector3dd(0, 0, 1));
		normals.add(Vector3dd(0, 0, 1));

		buffers.positionVBO.build();
		buffers.positionVBO.send(positions.get());

		buffers.normalVBO.build();
		buffers.normalVBO.send(normals.get());

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
	}
	*/

	{
		std::array<Graphics::Imageuc, 6> images;
		for (int i = 0; i < 6; ++i) {
			Graphics::Imageuc im(128, 128);
			images[i] = im;
		}
		textures.importanceTex.create();
		textures.importanceTex.send(images);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textures.importanceTex.getHandle());
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	/*
	{
		this->fbo2.create();
		this->fbo2.bind();
		//glBindFramebuffer(GL_FRAMEBUFFER, this->fbo2.getHandle());
		glBindRenderbuffer(GL_RENDERBUFFER, this->rbo.getHandle());
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rbo.getHandle());
		this->fbo2.unbind();
	}
	*/
}

void IBLShader::render(const Camera& camera, const int width, const int height)
{
	/*
	{
		buffers.fbo.bind();
		//this->cubeMapTex.bind(0);

		for (int i = 0; i < 6; ++i) {
			glViewport(0, 0, 512, 512);
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->textures.cubeMapTex.getHandle(), 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderers.cubeMapRenderer.buffer.projectionMatrix = ::captureProjection;
			renderers.cubeMapRenderer.buffer.viewMatrix = ::captureViews[i];
			renderers.cubeMapRenderer.buffer.texture = &this->textures.hdrTex;

			renderers.cubeMapRenderer.render();
		}

		this->textures.cubeMapTex.unbind();
		buffers.fbo.unbind();
	}

	{
		buffers.fbo.bind();

		renderers.irradianceRenderer.buffer.cubeMapTex = &textures.cubeMapTex;

		for (int i = 0; i < 6; ++i) {
			glViewport(0, 0, 32, 32);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->textures.irradianceTex.getHandle(), 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderers.irradianceRenderer.buffer.projectionMatrix = ::captureProjection;
			renderers.irradianceRenderer.buffer.viewMatrix = ::captureViews[i];
			renderers.irradianceRenderer.buffer.cubeMapTex = &this->textures.cubeMapTex;

			renderers.irradianceRenderer.render();
		}

		buffers.fbo.unbind();

	}
	*/

	/*
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		diffuseRenderer.buffer.modelMatrix = camera.getModelMatrix();
		diffuseRenderer.buffer.viewMatrix = camera.getViewMatrix();
		diffuseRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		diffuseRenderer.buffer.eyePosition = camera.getEye();
		diffuseRenderer.buffer.irradianceMapTex = &this->irradianceTex;
		diffuseRenderer.buffer.position = &this->positionVBO;
		diffuseRenderer.buffer.normal = &this->normalVBO;
		diffuseRenderer.buffer.albedo = Vector3df(1, 0, 0);
		diffuseRenderer.buffer.metalic = 0.7;
		diffuseRenderer.buffer.ao = 0.5;
		diffuseRenderer.buffer.indices = indices;
		diffuseRenderer.render();
	}
	*/

	{
//		buffers.fbo.bind();
//		buffers.fbo.setTexture(this->textures.brdfLutTex);
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderers.brdfLutRenderer.render();
		//buffers.fbo.unbind();
	}

	/*
	{
		buffers.fbo.bind();

		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rbo.getHandle());

		const unsigned int maxMipLevels = 5;
		for (unsigned int mip = 0; mip < maxMipLevels; mip++) {
			const unsigned int mipWidth = 128 * std::pow(0.5, mip);
			const unsigned int mipHeight = 128 * std::pow(0.5, mip);
			glBindRenderbuffer(GL_RENDERBUFFER, buffers.rbo.getHandle());
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);

			glViewport(0, 0, mipWidth, mipHeight);


			const auto roughness = (float)mip / (float)(maxMipLevels - 1);

			renderers.importanceRenderer.buffer.evnMapTex = &textures.cubeMapTex;
			renderers.importanceRenderer.buffer.projectionMatrix = ::captureProjection;
			renderers.importanceRenderer.buffer.roughness = roughness;

			for (unsigned int i = 0; i < 6; ++i) {
				renderers.importanceRenderer.buffer.viewMatrix = ::captureViews[i];
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, textures.importanceTex.getHandle(), mip);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				renderers.importanceRenderer.render();
			}
		}
		buffers.fbo.unbind();
	}
	*/

	/*
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderers.skyBoxRenderer.buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
		renderers.skyBoxRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		renderers.skyBoxRenderer.buffer.cubeMapTexture = &this->importanceTex;
		renderers.skyBoxRenderer.render();
	}
	*/

	/*
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderers.specularRenderer.buffer.position = &buffers.positionVBO;
		renderers.specularRenderer.buffer.normal = &buffers.normalVBO;
		renderers.specularRenderer.buffer.indices = this->indices;
		renderers.specularRenderer.buffer.eyePosition = camera.getEye();
		renderers.specularRenderer.buffer.viewMatrix = camera.getViewMatrix();
		renderers.specularRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		renderers.specularRenderer.buffer.modelMatrix = camera.getModelMatrix();
		renderers.specularRenderer.buffer.metalic = 0.1;
		renderers.specularRenderer.buffer.ao = 0.1;
		renderers.specularRenderer.buffer.albedo = Vector3df(1, 1, 1);
		renderers.specularRenderer.buffer.importanceMapTex = &this->textures.importanceTex;
		renderers.specularRenderer.buffer.irradianceMapTex = &this->textures.irradianceTex;
		renderers.specularRenderer.buffer.brdfLutTex = &this->textures.brdfLutTex;

		renderers.specularRenderer.render();
	}
	*/
}