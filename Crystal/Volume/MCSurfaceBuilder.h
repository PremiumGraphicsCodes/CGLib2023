#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Triangle3d.h"
#include "CGLib/Math/Box3d.h"
#include "Volume.h"

#include "MCCell.h"
#include "SparseVolume.h"

namespace Crystal {
	namespace Volume {

class MCSurfaceBuilder
{
public:
	void build(const Volume<float>& volume, const double isoLevel);

	//void build(const SparseVolume<float>& volume, const float isoLevel);

	int march(const MCCell& cell, const double isoLevel);

	std::vector<Math::Triangle3df> getTriangles() const { return triangles; }

private:
	Math::Vector3df getInterpolatedPosition(const float isolevel, const MCCell::Vertex& v1, const MCCell::Vertex& v2);

	std::vector<Math::Triangle3df> triangles;
};

	}
}