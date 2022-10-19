#include "IBLShader.h"
#include "CGLib/Shader/ShaderObject.h"
#include "CGLib/Shader/ShaderBuilder.h"
//#include "../CrystalRenderer/HDRImage.h"

#include "CGLib/Shader/VertexBuffer.h"

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
	HDRImageFileReader reader;
	reader.read("../../../ThirdParty/hdr/newport_loft.hdr");

	Imagef hdr = reader.toImage();
	textures.hdrTex.create();
	sendHDRTexture(hdr, textures.hdrTex);

	buffers.fbo.create();
	buffers.fbo.bind();
	buffers.depth.create();
	buffers.depth.bind();
	buffers.depth.setStorage(GL_DEPTH_COMPONENT, 512, 512);
	buffers.fbo.setRenderBuffer(GL_DEPTH_ATTACHMENT, &buffers.depth);
	buffers.depth.unbind();
	buffers.fbo.unbind();

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
	textures.irradianceTex.bind();
	//glBindTexture(GL_TEXTURE_CUBE_MAP, textures.irradianceTex.getHandle());
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	textures.irradianceTex.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	textures.irradianceTex.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	textures.irradianceTex.setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	textures.irradianceTex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	textures.irradianceTex.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	textures.irradianceTex.unbind();


	ShaderBuilder shaderBuilder;

	shaderBuilder.buildFromFile("../GLSL/CubeMap.vs", "../GLSL/CubeMap.fs");
	renderers.cubeMap.setShader(shaderBuilder.getShader());
	renderers.cubeMap.link();

	shaderBuilder.buildFromFile("../GLSL/Irradiance.vs", "../GLSL/Irradiance.fs");
	renderers.irradiance.setShader(shaderBuilder.getShader());
	renderers.irradiance.link();

	shaderBuilder.buildFromFile("../GLSL/IBLDiffuse.vs", "../GLSL/IBLDiffuse.fs");
	renderers.diffuse.setShader(shaderBuilder.getShader());
	renderers.diffuse.link();

	shaderBuilder.buildFromFile("../GLSL/BRDFLUT.vs", "../GLSL/BRDFLUT.fs");
	renderers.brdfLut.setShader(shaderBuilder.getShader());
	renderers.brdfLut.link();

	shaderBuilder.buildFromFile("../GLSL/Importance.vs", "../GLSL/Importance.fs");
	renderers.importance.setShader(shaderBuilder.getShader());
	renderers.importance.link();

	shaderBuilder.buildFromFile("../GLSL/IBLSpecular.vs", "../GLSL/IBLSpecular.fs");
	renderers.specular.setShader(shaderBuilder.getShader());
	renderers.specular.link();

	shaderBuilder.buildFromFile("../GLSL/SkyBox.vs", "../GLSL/SkyBox.fs");
	renderers.skyBox.setShader(shaderBuilder.getShader());
	renderers.skyBox.link();

	shaderBuilder.buildFromFile("../GLSL/Tex.vs", "../GLSL/Tex.fs");
	renderers.tex.setShader(shaderBuilder.getShader());
	renderers.tex.link();

	{
		VertexBuffer<float> positions;
		positions.add(Vector3df(0.0, 0.0, 0.0));
		positions.add(Vector3df(1.0, 0.0, 0.0));
		positions.add(Vector3df(1.0, 1.0, 0.0));
		positions.add(Vector3df(0.0, 1.0, 0.0));

		VertexBuffer<float> normals;
		normals.add(Vector3df(0, 0, 1));
		normals.add(Vector3df(0, 0, 1));
		normals.add(Vector3df(0, 0, 1));
		normals.add(Vector3df(0, 0, 1));

		buffers.positionVBO.create();
		buffers.positionVBO.send(positions);

		buffers.normalVBO.create();
		buffers.normalVBO.send(normals);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
	}

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
	{
		buffers.fbo.bind();
		//this->textures.cubeMapTex.bind();

		for (int i = 0; i < 6; ++i) {
			glViewport(0, 0, 512, 512);
			glClearColor(0.0, 0.0, 0.0, 0.0);
		
			buffers.fbo.setTexture(this->textures.cubeMapTex, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			assert(GL_NO_ERROR == glGetError());

			renderers.cubeMap.buffer.projectionMatrix = ::captureProjection;
			renderers.cubeMap.buffer.viewMatrix = ::captureViews[i];
			renderers.cubeMap.buffer.texture = &this->textures.hdrTex;

			renderers.cubeMap.render();
		}

		this->textures.cubeMapTex.unbind();
		buffers.fbo.unbind();
	}

	{
		buffers.fbo.bind();
		//buffers.fbo.setTexture(textures.irradianceTex);

		assert(GL_NO_ERROR == glGetError());


		renderers.irradiance.buffer.cubeMapTex = &textures.cubeMapTex;

		for (int i = 0; i < 6; ++i) {
			glViewport(0, 0, 32, 32);

			buffers.fbo.setTexture(this->textures.irradianceTex, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);


			//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->textures.irradianceTex.getHandle(), 0);

			assert(GL_NO_ERROR == glGetError());

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderers.irradiance.buffer.projectionMatrix = ::captureProjection;
			renderers.irradiance.buffer.viewMatrix = ::captureViews[i];
			renderers.irradiance.buffer.cubeMapTex = &this->textures.cubeMapTex;

			renderers.irradiance.render();

			assert(GL_NO_ERROR == glGetError());
		}

		//this->textures.importanceTex.unbind();
		buffers.fbo.unbind();

	}

	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderers.diffuse.buffer.modelMatrix = camera.getModelMatrix();
		renderers.diffuse.buffer.viewMatrix = camera.getViewMatrix();
		renderers.diffuse.buffer.projectionMatrix = camera.getProjectionMatrix();
		renderers.diffuse.buffer.eyePosition = camera.getEye();
		renderers.diffuse.buffer.irradianceMapTex = &this->textures.irradianceTex;
		renderers.diffuse.buffer.position = &this->buffers.positionVBO;
		renderers.diffuse.buffer.normal = &this->buffers.normalVBO;
		renderers.diffuse.buffer.albedo = Vector3df(1, 0, 0);
		renderers.diffuse.buffer.metalic = 0.7;
		renderers.diffuse.buffer.ao = 0.5;
		renderers.diffuse.buffer.indices = indices;
		renderers.diffuse.render();
	}

	{
		buffers.fbo.bind();
		buffers.fbo.setTexture(this->textures.brdfLutTex);
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderers.brdfLut.render();
		buffers.fbo.unbind();
	}

	{
		buffers.fbo.bind();

		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rbo.getHandle());

		const unsigned int maxMipLevels = 5;
		for (unsigned int mip = 0; mip < maxMipLevels; mip++) {
			const unsigned int mipWidth = 128 * std::pow(0.5, mip);
			const unsigned int mipHeight = 128 * std::pow(0.5, mip);

			buffers.rbo.bind();
			buffers.rbo.setStorage(GL_DEPTH_COMPONENT24, mipWidth, mipHeight);

			glViewport(0, 0, mipWidth, mipHeight);


			const auto roughness = (float)mip / (float)(maxMipLevels - 1);

			renderers.importance.buffer.evnMapTex = &textures.cubeMapTex;
			renderers.importance.buffer.projectionMatrix = ::captureProjection;
			renderers.importance.buffer.roughness = roughness;

			for (unsigned int i = 0; i < 6; ++i) {
				renderers.importance.buffer.viewMatrix = ::captureViews[i];
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, textures.importanceTex.getHandle(), mip);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				renderers.importance.render();
			}
		}
		buffers.fbo.unbind();
	}

	/*
		{
			glViewport(0, 0, width, height);
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			renderers.skyBox.buffer.modelViewMatrix = glm::mat4(glm::mat3(camera.getModelViewMatrix()));
			renderers.skyBox.buffer.projectionMatrix = camera.getProjectionMatrix();
			renderers.skyBox.buffer.cubeMapTexture = &this->textures.irradianceTex;
			renderers.skyBox.render();
		}
		*/
		/*
	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderers.tex.buffer.tex = &textures.hdrTex;
		renderers.tex.render();
	}
	*/

	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderers.specular.buffer.position = &buffers.positionVBO;
		renderers.specular.buffer.normal = &buffers.normalVBO;
		renderers.specular.buffer.indices = this->indices;
		renderers.specular.buffer.eyePosition = camera.getEye();
		renderers.specular.buffer.viewMatrix = camera.getViewMatrix();
		renderers.specular.buffer.projectionMatrix = camera.getProjectionMatrix();
		renderers.specular.buffer.modelMatrix = camera.getModelMatrix();
		renderers.specular.buffer.metalic = 0.1;
		renderers.specular.buffer.ao = 0.1;
		renderers.specular.buffer.albedo = Vector3df(1, 1, 1);
		renderers.specular.buffer.importanceMapTex = &this->textures.importanceTex;
		renderers.specular.buffer.irradianceMapTex = &this->textures.irradianceTex;
		renderers.specular.buffer.brdfLutTex = &this->textures.brdfLutTex;

		renderers.specular.render();
	}
}