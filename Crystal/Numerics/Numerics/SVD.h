
#pragma once

#include "CGLib/Math/Vector2d.h"
#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Matrix2d.h"
#include "CGLib/Math/Matrix3d.h"
#include "CGLib/Math/Matrix4d.h"

namespace Crystal {
	namespace Numerics {

class SVD2d
{
public:
	struct Result
	{
		bool isOk;
		Math::Vector2dd eigenValues;
		Math::Matrix2dd eigenVectors;
	};

	Result calculate(const Math::Matrix2dd& lhs);
};

class SVD3d
{
	struct Result
	{
		bool isOk;
		Math::Vector3dd eigenValues;
		Math::Matrix3dd eigenVectors;
	};

	Result calculate(const Math::Matrix3dd& lhs);

	Result calculateJacobi(const Math::Matrix3dd& lhs);
};
	}
}