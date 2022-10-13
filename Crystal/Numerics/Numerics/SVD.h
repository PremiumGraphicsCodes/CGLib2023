
#pragma once

#include "CGLib/Math/Vector2d.h"
#include "CGLib/Math/Matrix2d.h"

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

	}
}