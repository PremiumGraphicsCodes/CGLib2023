#pragma once

#include "Vector3d.h"
#include "ISurface3d.h"

namespace Crystal {
	namespace Math {

class Rectangle3d : public ISurface3dd
{
public:
	Rectangle3d();

	Rectangle3d(const Vector3dd& origin, const Vector3dd& uvec, const Vector3dd& vvec);

	Vector3dd getPosition(const double u, const double v) const override;

	Vector3dd getNormal() const;

private:
	Vector3dd origin;
	Vector3dd uvec;
	Vector3dd vvec;
};

	}
}