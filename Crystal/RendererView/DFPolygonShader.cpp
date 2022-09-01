#include "DFPolygonShader.h"

#include "CGLib/Graphics/ImageFileReader.h"
#include "CGLib/Shader/ShaderBuilder.h"
#include "CGLib/Shader/VertexBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	bool readTexture(TextureObject& cubeMap)
	{
		ImageFileReader reader;
		if (!reader.read("../../ThirdParty/forest-skyboxes/Brudslojan/posx.jpg")) {
			return false;
		}
		cubeMap.send(reader.toImage());
		return true;
	}
}


void DFPolygonShader::build()
{
	ShaderBuilder builder;
	
	builder.buildFromFile("../GLSL/DFAlbedo.vs", "../GLSL/DFAlbedo.fs");
	albedoRenderer.setShader(builder.getShader());
	albedoRenderer.link();
	
	builder.buildFromFile("../GLSL/DFGeometry.vs", "../GLSL/DFGeometry.fs");
	gRenderer.setShader(builder.getShader());
	gRenderer.link();

	builder.buildFromFile("../GLSL/DFLight.vs", "../GLSL/DFLight.fs");
	lightRenderer.setShader(builder.getShader());
	lightRenderer.link();

	builder.buildFromFile("../GLSL/Tex.vs", "../GLSL/Tex.fs");
	texRenderer.setShader(builder.getShader());
	texRenderer.link();

	this->fbo.create();

	this->albedoTexture.create();
	this->albedoTexture.send(Imageuc(512, 512));

	this->polygonTexture.create();
	this->polygonTexture.send(Imageuc(512, 512));// , 255));

	this->polygonTexture.create();
	this->positionTexture.send(Imagef(512, 512));

	this->normalTexture.create();
	this->normalTexture.send(Imagef(512, 512));

	this->shadedTexture.create();
	this->shadedTexture.send(Imagef(512, 512));

	readTexture(this->polygonTexture);

	{
		Shader::VertexBuffer<float> pb;
		pb.add(Vector3df(0.0, 0.0, 0.0));
		pb.add(Vector3df(1.0, 0.0, 0.0));
		pb.add(Vector3df(1.0, 1.0, 0.0));
		pb.add(Vector3df(0.0, 1.0, 0.0));
		this->positions.create();
		this->positions.send(pb);
	}

	{
		Shader::VertexBuffer<float> texCoords;
		texCoords.add(Vector2df(0.0, 0.0));
		texCoords.add(Vector2df(1.0, 0.0));
		texCoords.add(Vector2df(1.0, 1.0));
		texCoords.add(Vector2df(0.0, 1.0));
		this->texCoords.create();
		this->texCoords.send(texCoords);
	}

	{
		Shader::VertexBuffer<float> normals;
		normals.add(Vector3df(0, 0, 1));
		normals.add(Vector3df(0, 0, 1));
		normals.add(Vector3df(0, 0, 1));
		normals.add(Vector3df(0, 0, 1));
		this->normals.create();
		this->normals.send(normals);
	}

	Crystal::Renderer::DFAlbedoRenderer::Buffer::FaceGroup fg1;
	fg1.indices.push_back(0);
	fg1.indices.push_back(1);
	fg1.indices.push_back(2);

	fg1.indices.push_back(0);
	fg1.indices.push_back(2);
	fg1.indices.push_back(3);

	fg1.texture = &this->polygonTexture;
	albedoRenderer.buffer.faceGroups.push_back(fg1);

	gRenderer.buffer.indices = fg1.indices;

	//Shader::PolygonRenderer::Buffer::FaceGroup fg2;
	//fg2.indices.push_back(0);
	//fg2.indices.push_back(2);
	//fg2.indices.push_back(3);

	//fg2.texture = this->polygonTexture;
	//buffer.faceGroups.push_back(fg2);
}

void DFPolygonShader::render(const Camera& camera, const int wwidth, const int hheight)
{
	const int width = 512;
	const int height = 512;
	{
		this->fbo.bind();
		this->fbo.setTexture(this->albedoTexture);

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		albedoRenderer.buffer.position = &positions;
		albedoRenderer.buffer.texCoord = &texCoords;
		albedoRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		albedoRenderer.buffer.modelViewMatrix = camera.getModelViewMatrix();

		this->albedoRenderer.render();

		this->fbo.unbind();
	}

	{
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->texRenderer.buffer.tex = &this->albedoTexture;
		texRenderer.render();
	}

	/*
	{
		this->fbo->bind();

		const GLenum bufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, bufs);

		//this->geometryTexture->bind(0);
		this->fbo->setTexture(*positionTexture);
		//this->normalTexture->bind(1);
		this->fbo->setTexture(*normalTexture, 1);

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->gRenderer.buffer.position.send(positions.get());
		this->gRenderer.buffer.normal.send(normals.get());
		this->gRenderer.buffer.projectionMatrix = camera.getProjectionMatrix();
		this->gRenderer.buffer.modelViewMatrix = camera.getModelViewMatrix();
		this->gRenderer.buffer.normalMatrix = glm::transpose(glm::inverse(glm::mat3(camera.getRotationMatrix())));

		this->gRenderer.render();

		this->fbo->unbind();

		//const GLenum bufs1[] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, bufs1);
	}

	{
		//		this->fbo->bind();

		//		const GLenum bufs[] = { GL_COLOR_ATTACHMENT0 };
		//		glDrawBuffers(1, bufs);

		//		this->fbo->setTexture(*shadedTexture);

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightRenderer.buffer.albedoTex = this->colorTexture.get();
		lightRenderer.buffer.positionTex = this->positionTexture.get();
		lightRenderer.buffer.normalTex = this->normalTexture.get();
		lightRenderer.buffer.invModelViewMatrix = glm::inverse(camera.getModelViewMatrix());
		lightRenderer.buffer.invProjectionMatrix = glm::inverse(camera.getProjectionMatrix());
		lightRenderer.buffer.invNormalMatrix = glm::inverse(glm::transpose(glm::inverse(glm::mat3(camera.getRotationMatrix()))));
		lightRenderer.buffer.lightPosition = Vector3dd(0, 0, 10);
		lightRenderer.buffer.lightColor = Vector3dd(1, 1, 1);

		this->lightRenderer.render();

		//		this->fbo->unbind();

	}
	*/
}