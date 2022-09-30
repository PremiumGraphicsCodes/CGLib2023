#pragma once

#include <array>
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Triangle3d
{
public:
Triangle3d();

explicit Triangle3d(const std::array<Vector3dd, 3>& vertices);

Triangle3d(const Vector3dd& v1, const Vector3dd& v2, const Vector3dd& v3);

Vector3dd getNormal() const;

std::array<Vector3dd, 3> getVertices() const { return vertices; }

bool isSame(const Triangle3d& rhs, const double tolerance) const;

private:
std::array<Vector3dd, 3> vertices;
};

	}
}