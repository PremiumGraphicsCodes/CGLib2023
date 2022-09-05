#include "CubeMapRenderer.h"

#include "CGLib/Math/Box3d.h"
#include "CGLib/Shader/TextureObject.h"
#include "CGLib/Shader/TextureUnit.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto viewMatrixLabel = "view";
	constexpr auto textureLabel = "equirectangularMap";
	constexpr auto positionLabel = "aPos";
	constexpr auto fragColorLabel = "FragColor";

	std::vector<float> toGLArray(const Box3df& volume)
	{
		const auto v0 = volume.getPosition(0, 0, 0);
		const auto v1 = volume.getPosition(1, 0, 0);
		const auto v2 = volume.getPosition(1, 1, 0);
		const auto v3 = volume.getPosition(0, 1, 0);

		const auto v4 = volume.getPosition(0, 0, 1);
		const auto v5 = volume.getPosition(1, 0, 1);
		const auto v6 = volume.getPosition(1, 1, 1);
		const auto v7 = volume.getPosition(0, 1, 1);

		std::vector<Vector3df> vertices = {
			v0, v1, v2,
			v2, v3, v0,
			v1, v5, v6,
			v6, v2, v1,
			v6, v5, v4,
			v4, v7, v6,
			v4, v0, v3,
			v7, v4, v3,
			v6, v3, v2,
			v7, v3, v6,
			v0, v5, v1,
			v0, v4, v5
		};

		std::vector<float> data;
		for (const auto& v : vertices) {
			data.push_back(v.x);
			data.push_back(v.y);
			data.push_back(v.z);
		}

		return data;
	}

	struct UniformLoc {
		GLuint projectionMatrix;
		GLuint viewMatrix;
		GLuint texture;
	};

	struct AttrLoc {
		GLuint position;
	};

	UniformLoc uniforms;
	AttrLoc attrs;
}

void CubeMapRenderer::link()
{
	uniforms.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
	uniforms.viewMatrix = shader->findUniformLocation(::viewMatrixLabel);
	uniforms.texture = shader->findUniformLocation(::textureLabel);

	attrs.position = shader->findAttribLocation(::positionLabel);
}

void CubeMapRenderer::render()
{
	shader->bind();

	const Box3df cube(Vector3df(-1, -1, -1), Vector3df(1, 1, 1));
	std::vector<float> positions = ::toGLArray(cube);

	assert(GL_NO_ERROR == glGetError());

	Uniform projectionMatrix(uniforms.projectionMatrix);
	Uniform viewMatrix(uniforms.viewMatrix);
	
	projectionMatrix.send(buffer.projectionMatrix);
	viewMatrix.send(buffer.viewMatrix);

	assert(GL_NO_ERROR == glGetError());

	TextureUnit texUnit(0, buffer.texture);
	Uniform texture(uniforms.texture);
	texture.send(texUnit);

	assert(GL_NO_ERROR == glGetError());

	VertexAttribute vertexAttr(attrs.position);
	vertexAttr.sendVertexAttribute3df(positions);

	shader->drawTriangles(positions.size() / 3);

	shader->bindOutput(::fragColorLabel);

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}