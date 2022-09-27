#include "gtest/gtest.h"
#include "../Math/Matrix2d.h"
#include "../Math/pi.h"

using namespace Crystal::Math;

namespace {
	const auto tolerance = 1.0e-6f;
	const auto pi = static_cast<float>(PI);
}

TEST(Matrix2dTest, TestRotationMatrix)
{
	const Matrix2df expected
	(
		0.0, -1.0,
		1.0, 0.0
	);
	const auto actual = rotationMatrix(0.5f * pi);
	EXPECT_TRUE(areSame(expected, actual, tolerance));
}