#include "PolygonMeshBuilder.h"

#include "CGLib/Math/ISurface3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

namespace {
	Vector3df calculateNormal(const ISurface3d<float>& surface, const float u, const float v)
	{
		const auto du = surface.getPosition(u + 0.01, v) - surface.getPosition(u, v);
		const auto dv = surface.getPosition(u, v + 0.01) - surface.getPosition(u, v);
		return glm::cross(glm::normalize(du), glm::normalize(dv));
	}
}

PolygonMeshBuilder::PolygonMeshBuilder() :
	nextVertexId(0),
	nextFaceId(0)
{}

void PolygonMeshBuilder::add(const ISurface3d<float>& surface, const int unum, const int vnum)
{
	assert(1 <= unum);
	assert(1 <= vnum);

	std::vector<std::vector<int>> grid;
	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		std::vector<int> g;
		for (int j = 0; j <= vnum; ++j) {
			const float v = j / static_cast<float>(vnum);
			PolygonMesh::Vertex vert;
			vert.position = surface.getPosition(u, v);
			vert.normal = ::calculateNormal(surface, u, v); //surface.getPosition()
			vert.texCoord = Vector2df(u, v);
		}
		grid.push_back(g);
	}

	/*
	for (int i = 0; i < unum; ++i) {
		for (int j = 0; j < vnum; ++j) {
			createFace(vertices[i][j], vertices[i + 1][j], vertices[i][j + 1]);
			createFace(vertices[i + 1][j + 1], vertices[i][j + 1], vertices[i + 1][j]);
		}
	}
	*/
}

int PolygonMeshBuilder::createVertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord)
{
	return -1;
}

//
//std::unique_ptr<PolygonMesh> PolygonMeshBuilder::build()
//{
//	auto mesh = std::make_unique<PolygonMesh>();
//	mesh->positions = positions;
//	mesh->normals = normals;
//	mesh->texCoords = texCoords;
//	mesh->vertices = vertices;
//	mesh->faces = faces;
//	return std::move(mesh);
//}
//
//void PolygonMeshBuilder::add(const int v0, const int v1, const int v2, const int v3)
//{
//	const auto& p0 = positions[v0];
//	const auto& p1 = positions[v1];
//	const auto& p2 = positions[v2];
//
//	const auto& normal = glm::cross(p1 - p0, p2 - p0);
//	auto n0 = createNormal(normal);
//
//	auto vv0 = createVertex(v0, n0);
//	auto vv1 = createVertex(v1, n0);
//	auto vv2 = createVertex(v2, n0);
//	auto vv3 = createVertex(v3, n0);
//
//	createFace(vv0, vv1, vv2);
//	createFace(vv0, vv2, vv3);
//}
//
//Vector3dd PolygonMeshBuilder::calculateNormal(const int v0, const int v1, const int v2)
//{
//	const auto& p0 = positions[v0];
//	const auto& p1 = positions[v1];
//	const auto& p2 = positions[v2];
//
//	return glm::normalize(glm::cross(p1 - p0, p2 - p0));
//}
//
//int PolygonMeshBuilder::createPosition(const Vector3dd& v)
//{
//	positions.push_back(v);
//	return static_cast<int>(positions.size() - 1);
//}
//
//int PolygonMeshBuilder::createNormal(const Vector3dd& v)
//{
//	normals.push_back(v);
//	return static_cast<int>(normals.size() - 1);
//}
//
//int PolygonMeshBuilder::createTexCoord(const Vector2dd& v)
//{
//	texCoords.push_back(v);
//	return static_cast<int>(texCoords.size() - 1);
//}
//
//int PolygonMeshBuilder::createVertex(const int positionId, const int normalId, const int texCoordId)
//{
//	Vertex v;
//	v.positionId = positionId;
//	v.normalId = normalId;
//	v.texCoordId = texCoordId;
//	v.id = nextVertexId++;
//	vertices.push_back(v);
//	return v.id;
//}
//
//int PolygonMeshBuilder::createFace(int v0, int v1, int v2)
//{
//	Face f(v0, v1, v2, nextFaceId++);
//	faces.push_back(f);
//	return f.getId();
//}