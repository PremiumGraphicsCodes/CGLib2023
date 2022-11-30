#include "PolygonMeshBuilder.h"

#include "CGLib/Math/ISurface3d.h"
#include "CGLib/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Mesh;

namespace {
	Vector3df calculateNormal(const ISurface3d<float>& surface, const float u, const float v)
	{
		const auto du = surface.getPosition(u + 0.01, v) - surface.getPosition(u, v);
		const auto dv = surface.getPosition(u, v + 0.01) - surface.getPosition(u, v);
		return glm::cross(glm::normalize(du), glm::normalize(dv));
	}
}

PolygonMeshBuilder::PolygonMeshBuilder()
{}

void PolygonMeshBuilder::add(const Sphere3d<float>& surface, const int unum, const int vnum)
{
	assert(1 <= unum);
	assert(1 <= vnum);

	std::vector<std::vector<int>> vertices;
	vertices.resize(unum + 1);
	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		vertices[i].resize(vnum + 1);
		for (int j = 0; j <= vnum; ++j) {
			const float v = j / static_cast<float>(vnum);
			const auto p = surface.getPosition(u, v);
			const auto n = glm::normalize( p - surface.getCenter() );
			//const auto n = ::calculateNormal(surface, u, v); //surface.getPosition()
			const auto t = Vector2df(u, v);
			const auto index = createVertex(p, n, t);
			vertices[i][j] = index;
		}
	}

	for (int i = 0; i < unum; ++i) {
		for (int j = 0; j < vnum; ++j) {
			createFace(vertices[i][j], vertices[i + 1][j], vertices[i][j + 1]);
			createFace(vertices[i + 1][j + 1], vertices[i][j + 1], vertices[i + 1][j]);
		}
	}
}

void PolygonMeshBuilder::add(const Box3d<float>& box)
{
	const int unum = 2;
	const int vnum = 2;
	const int wnum = 2;
	assert(1 <= unum);
	assert(1 <= vnum);
	assert(1 <= wnum);

	std::vector<std::vector<std::vector<int>>> grid;
	grid.resize(unum + 1);
	for (int i = 0; i <= unum; ++i) {
		grid[i].resize(vnum + 1);
		const float u = i / static_cast<float>(unum);
		for (int j = 0; j <= vnum; ++j) {
			grid[i][j].resize(wnum + 1);
			const float v = j / static_cast<float>(vnum);
			for (int k = 0; k <= wnum; ++k) {
				const float w = k / static_cast<float>(wnum);
				const auto index = createVertex(box.getPosition(u, v, w), Vector3df(0,1,0), Vector2df(0,0));
				grid[i][j][k] = index;
			}
		}
	}
	for (int i = 0; i < grid.size() - 1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			for (int k = 0; k < grid[i][j].size() - 1; ++k) {
				const auto v1 = grid[i][j][k];
				const auto v2 = grid[i + 1][j][k];
				const auto v3 = grid[i + 1][j + 1][k];
				const auto v4 = grid[i][j + 1][k];

				const auto v5 = grid[i][j][k + 1];
				const auto v6 = grid[i + 1][j][k + 1];
				const auto v7 = grid[i + 1][j + 1][k + 1];
				const auto v8 = grid[i][j + 1][k + 1];
				createFace(v1, v2, v4);
				//createFace(vertices[i + 1][j + 1], vertices[i][j + 1], vertices[i + 1][j]);
			}
		}
	}
}

int PolygonMeshBuilder::createVertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord)
{
	auto v = std::make_unique<PolygonMesh::Vertex>();
	v->position = position;
	v->normal = normal;
	v->texCoord = texCoord;
	vertices.push_back(std::move(v));
	return vertices.size() - 1;
}


std::unique_ptr<PolygonMesh> PolygonMeshBuilder::build()
{
	auto mesh = std::make_unique<PolygonMesh>();
	for (const auto& f : faces) {
		mesh->addFace(f);
	}
	for (auto& v : vertices) {
		mesh->addVertex(std::move(v));
	}
	return std::move(mesh);
}

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

int PolygonMeshBuilder::createFace(int v0, int v1, int v2)
{
	PolygonMesh::Face f;
	f.v0 = v0;
	f.v1 = v1;
	f.v2 = v2;
	faces.push_back(f);
	return faces.size()-1;
}