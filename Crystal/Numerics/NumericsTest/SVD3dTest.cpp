#include "pch.h"

#include "../Numerics/SVD3d.h"

#include "CGLib/Math/pi.h"

using namespace Crystal::Math;
using namespace Crystal::Numerics;

namespace {
	constexpr auto tolerance = 1.0e-6;
}

TEST(SVD3dTest, TestCalculate)
{
	{
		Matrix3dd m = rotationMatrixX(0.5 * PI);
		SVD3d svd;
		const auto actual = svd.calculate(m);
		const auto values = actual.eigenValues;
		EXPECT_NEAR(-1.0, values[0], tolerance);
		EXPECT_NEAR(1.0, values[1], tolerance);
		EXPECT_NEAR(1.0, values[2], tolerance);
	}
	{
		Matrix3dd m = rotationMatrixX(PI);
		SVD3d svd;
		const auto actual = svd.calculate(m);
		const auto values = actual.eigenValues;
		EXPECT_NEAR(-1.0, values[0], tolerance);
		EXPECT_NEAR(-1.0, values[1], tolerance);
		EXPECT_NEAR(1.0, values[2], tolerance);
	}
}