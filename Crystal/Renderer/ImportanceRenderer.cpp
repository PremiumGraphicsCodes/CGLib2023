#include "ImportanceRenderer.h"

#include "CGLib/Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Renderer;

namespace {
	constexpr auto envMapTex = "environmentMap";
	constexpr auto roughness = "roughness";
	constexpr auto positionLabel = "aPos";
	constexpr auto projectionMatrix = "projection";
	constexpr auto viewMatrix = "view";

	/*

	std::vector<float> toGLArray(const Box3dd& volume)
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
	*/
}


ImportanceRenderer::ImportanceRenderer()
{}

void ImportanceRenderer::link()
{
	shader->findAttribLocation(::positionLabel);
	shader->findUniformLocation(::roughness);
	shader->findUniformLocation(::envMapTex);
	shader->findUniformLocation(::projectionMatrix);
	shader->findUniformLocation(::viewMatrix);
}

void ImportanceRenderer::render()
{
	/*
	const GLCube cube(Vector3df(-1, -1, -1), Vector3df(1, 1, 1));
	std::vector<float> positions = cube.toGLArray();

	shader->bind();

	shader->bindOutput("FragColor");

	buffer.evnMapTex->bind(0);

	shader->sendUniform(::envMapTex, 0);
	shader->sendUniform(::roughness, buffer.roughness);
	shader->sendUniform(::projectionMatrix, buffer.projectionMatrix);
	shader->sendUniform(::viewMatrix, buffer.viewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, positions);

	glEnableVertexAttribArray(0);
	shader->drawTriangles(positions.size() / 3);
	glDisableVertexAttribArray(0);


	buffer.evnMapTex->unbind();

	shader->unbind();
	*/
}