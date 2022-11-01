#include "TriangleMeshBuilder.h"

#include "../Math/ISurface3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TriangleMeshBuilder::TriangleMeshBuilder()
{
}

std::unique_ptr<TriangleMesh> TriangleMeshBuilder::build()
{
	auto mesh = std::make_unique<TriangleMesh>();
	for (const auto& f : faces) {
		mesh->addFace(f);
	}
	return std::move(mesh);
}

void TriangleMeshBuilder::add(const ISurface3df& surface, const int unum, const int vnum)
{
	assert(1 <= unum);
	assert(1 <= vnum);

	std::vector<std::vector<Vector3df>> positions;
	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		std::vector<Vector3df> g;
		for (int j = 0; j <= vnum; ++j) {
			const float v = j / static_cast<float>(vnum);
			g.push_back( surface.getPosition(u, v));
		}
		positions.push_back(g);
	}
	for (int i = 0; i < positions.size() - 1; ++i) {
		for (int j = 0; j < positions[i].size() - 1; ++j) {
			const Triangle3df t1({ positions[i][j], positions[i + 1][j], positions[i][j + 1] });
			faces.push_back(TriangleFace(t1));
			const Triangle3df t2({ positions[i + 1][j + 1], positions[i][j + 1], positions[i + 1][j] });
			faces.push_back(TriangleFace(t2));
		}
	}
}

/*
void TriangleMeshBuilder::add(const IVolume3dd& volume, const int unum, const int vnum, const int wnum)
{
	const auto v0 = volume.getPosition(0, 0, 0);
	const auto v1 = volume.getPosition(1, 0, 0);
	const auto v2 = volume.getPosition(1, 1, 0);
	const auto v3 = volume.getPosition(0, 1, 0);

	const auto v4 = volume.getPosition(0, 0, 1);
	const auto v5 = volume.getPosition(1, 0, 1);
	const auto v6 = volume.getPosition(1, 1, 1);
	const auto v7 = volume.getPosition(0, 1, 1);

	addFace(v0, v1, v2); // front
	addFace(v2, v3, v0);

	addFace(v1, v5, v6); // right
	addFace(v6, v2, v1);

	addFace(v6, v5, v4); // left
	addFace(v4, v7, v6);

	addFace(v4, v0, v3); // back
	addFace(v7, v4, v3);

	addFace(v6, v3, v2); // top;
	addFace(v7, v3, v6);

	addFace(v0, v5, v1); // bottom
	addFace(v0, v4, v5);
}
*/