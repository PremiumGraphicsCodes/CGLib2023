#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Matrix3d.h"

namespace Crystal {
	namespace Numerics {

class SVD3d
{
public:
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