#pragma once

#include "../Renderer/PointRenderer.h"
#include "../Scene/ParticleSystemScene.h"
#include "CGLib/Shader/VertexBuffer.h"
#include "CGLib/Graphics/Camera.h"

namespace Crystal {
	namespace UI {

class Renderer
{
public:
	void build();

	void render(const Graphics::Camera& camera, Scene::ParticleSystemScene* scene);

private:
	struct VBO {
		Shader::VertexBufferObject point;
		Shader::VertexBufferObject color;
		Shader::VertexBufferObject size;
	};
	struct Buffer {
		Shader::VertexBuffer<float> position;
		Shader::VertexBuffer<float> color;
		Shader::VertexBuffer<float> size;
	};
	//Buffer buffer;
	VBO vbo;
	Crystal::Renderer::PointRenderer point;
};
	}
}
