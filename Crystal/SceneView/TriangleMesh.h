#pragma once

#include "CGLib/Shape/IShape.h"
#include "CGLib/Math/Triangle3d.h"

#include <vector>

namespace Crystal {
	namespace Shape {

class TriangleFace
{
public:
	TriangleFace() = default;

	explicit TriangleFace(const Math::Triangle3df& triangle);

	TriangleFace(const Math::Triangle3df& triangle, const Math::Vector3dd& normal) :
		triangle(triangle),
		normal(normal)
	{}

	Math::Triangle3df triangle;
	Math::Vector3dd normal;
};

class TriangleMesh : public IShape
{
public:
	TriangleMesh();

	~TriangleMesh();

	void clear();

	Math::Box3df getBoundingBox() const override;

	std::vector<TriangleFace> getFaces() const { return faces; }

	void addFace(const TriangleFace& face);

public:
	std::vector<TriangleFace> faces;
};

	}
}